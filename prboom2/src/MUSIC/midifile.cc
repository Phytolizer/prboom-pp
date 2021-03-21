// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 2009 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
// DESCRIPTION:
//    Reading of MIDI files.
//
//-----------------------------------------------------------------------------

#include "cpp/enums/midi_event_type_t.hh"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>

#ifndef TEST
#include "doomdef.hh"
#include "doomtype.hh"
#else
typedef enum
{
    false,
    true
} dboolean;
typedef unsigned char byte;
#define PACKEDATTR __attribute__((packed))
#endif
#include "lprintf.hh"
#include "midifile.hh"

#define HEADER_CHUNK_ID "MThd"
#define TRACK_CHUNK_ID "MTrk"
#define MAX_BUFFER_SIZE 0x10000

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef ntohl
#ifdef WORDS_BIGENDIAN
#define ntohl
#define ntohs
#else // WORDS_BIGENDIAN

#define ntohl(x)                                                               \
    (/*(long int)*/ ((((unsigned long int)(x)&0x000000ffU) << 24) |            \
                     (((unsigned long int)(x)&0x0000ff00U) << 8) |             \
                     (((unsigned long int)(x)&0x00ff0000U) >> 8) |             \
                     (((unsigned long int)(x)&0xff000000U) >> 24)))

#define ntohs(x)                                                               \
    (/*(short int)*/ ((((unsigned short int)(x)&0x00ff) << 8) |                \
                      (((unsigned short int)(x)&0xff00) >> 8)))
#endif // WORDS_BIGENDIAN
#endif // ntohl

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

#ifdef _MSC_VER
#pragma pack(pop)
#endif

struct midi_track_t
{
    // Length in bytes:

    unsigned int data_len;

    // Events in this track:

    std::vector<midi_event_t> events;
};

// Check the header of a chunk:

static dboolean CheckChunkHeader(chunk_header_t *chunk, const char *expected_id)
{
    dboolean result;

    result = (memcmp((char *)chunk->chunk_id, expected_id, 4) == 0);

    if (!result)
    {
        lprintf(LO_WARN,
                "CheckChunkHeader: Expected '%s' chunk header, "
                "got '%c%c%c%c'\n",
                expected_id, chunk->chunk_id[0], chunk->chunk_id[1],
                chunk->chunk_id[2], chunk->chunk_id[3]);
    }

    return result;
}

// Read a single byte.  Returns false on error.

static dboolean ReadByte(byte *result, midimem_t *mf)
{
    if (mf->pos >= mf->len)
    {
        lprintf(LO_WARN, "ReadByte: Unexpected end of file\n");
        return false;
    }

    *result = mf->data[mf->pos++];
    return true;
}

static dboolean ReadMultipleBytes(void *dest, size_t len, midimem_t *mf)
{
    byte *cdest = (byte *)dest;
    unsigned i;
    for (i = 0; i < len; i++)
    {
        if (!ReadByte(cdest + i, mf))
        {
            lprintf(LO_WARN, "ReadMultipleBytes: Unexpected end of file\n");
            return false;
        }
    }
    return true;
}

// Read a variable-length value.

static dboolean ReadVariableLength(unsigned int *result, midimem_t *mf)
{
    int i;
    byte b;

    *result = 0;

    for (i = 0; i < 4; ++i)
    {
        if (!ReadByte(&b, mf))
        {
            lprintf(LO_WARN, "ReadVariableLength: Error while reading "
                             "variable-length value\n");
            return false;
        }

        // Insert the bottom seven bits from this byte.

        *result <<= 7;
        *result |= b & 0x7f;

        // If the top bit is not set, this is the end.

        if ((b & 0x80) == 0)
        {
            return true;
        }
    }

    lprintf(LO_WARN, "ReadVariableLength: Variable-length value too "
                     "long: maximum of four bytes\n");
    return false;
}

// Read a byte sequence into the data buffer.

static void *ReadByteSequence(unsigned int num_bytes, midimem_t *mf)
{
    unsigned int i;
    byte *result;

    // events can be length 0.  malloc(0) is not portable (can return nullptr)
    if (!num_bytes)
    {
        return malloc(4);
    }

    // Allocate a buffer:

    result = (byte *)malloc(num_bytes);

    if (result == nullptr)
    {
        lprintf(LO_WARN,
                "ReadByteSequence: Failed to allocate buffer %u bytes\n",
                num_bytes);
        return nullptr;
    }

    // Read the data:

    for (i = 0; i < num_bytes; ++i)
    {
        if (!ReadByte(&result[i], mf))
        {
            lprintf(LO_WARN, "ReadByteSequence: Error while reading byte %u\n",
                    i);
            free(result);
            return nullptr;
        }
    }

    return result;
}

// Read a MIDI channel event.
// two_param indicates that the event type takes two parameters
// (three byte) otherwise it is single parameter (two byte)

static dboolean ReadChannelEvent(midi_event_t *event, byte event_type,
                                 dboolean two_param, midimem_t *mf)
{
    byte b;

    // Set basics:

    event->event_type = (midi_event_type_t::Type)(event_type & 0xf0);
    event->data.setChannel();
    event->data.channel().channel = event_type & 0x0f;

    // Read parameters:

    if (!ReadByte(&b, mf))
    {
        lprintf(LO_WARN, "ReadChannelEvent: Error while reading channel "
                         "event parameters\n");
        return false;
    }

    event->data.channel().param1 = b;

    // Second parameter:

    if (two_param)
    {
        if (!ReadByte(&b, mf))
        {
            lprintf(LO_WARN, "ReadChannelEvent: Error while reading channel "
                             "event parameters\n");
            return false;
        }

        event->data.channel().param2 = b;
    }

    return true;
}

// Read sysex event:

static dboolean ReadSysExEvent(midi_event_t *event, byte event_type,
                               midimem_t *mf)
{
    event->event_type = midi_event_type_t::Type{event_type};

    event->data.setSysex();
    if (!ReadVariableLength(&event->data.sysex().length, mf))
    {
        lprintf(LO_WARN, "ReadSysExEvent: Failed to read length of "
                         "SysEx block\n");
        return false;
    }

    // Read the byte sequence:

    event->data.sysex().data =
        (byte *)ReadByteSequence(event->data.sysex().length, mf);

    if (event->data.sysex().data == nullptr)
    {
        lprintf(LO_WARN, "ReadSysExEvent: Failed while reading SysEx event\n");
        return false;
    }

    return true;
}

// Read meta event:

static dboolean ReadMetaEvent(midi_event_t *event, midimem_t *mf)
{
    byte b;

    event->event_type = midi_event_type_t::META;

    // Read meta event type:

    if (!ReadByte(&b, mf))
    {
        lprintf(LO_WARN, "ReadMetaEvent: Failed to read meta event type\n");
        return false;
    }

    event->data.setMeta();
    event->data.meta().type = midi_meta_event_type_t::Type{b};

    // Read length of meta event data:

    if (!ReadVariableLength(&event->data.meta().length, mf))
    {
        lprintf(LO_WARN, "ReadMetaEvent: Failed to read length of "
                         "MetaEvent block\n");
        return false;
    }

    // Read the byte sequence:

    event->data.meta().data =
        (byte *)ReadByteSequence(event->data.meta().length, mf);

    if (event->data.meta().data == nullptr)
    {
        lprintf(LO_WARN, "ReadMetaEvent: Failed while reading MetaEvent\n");
        return false;
    }

    return true;
}

static dboolean ReadEvent(midi_event_t *event, unsigned int *last_event_type,
                          midimem_t *mf)
{
    byte event_type;

    if (!ReadVariableLength(&event->delta_time, mf))
    {
        lprintf(LO_WARN, "ReadEvent: Failed to read event timestamp\n");
        return false;
    }

    if (!ReadByte(&event_type, mf))
    {
        lprintf(LO_WARN, "ReadEvent: Failed to read event type\n");
        return false;
    }

    // All event types have their top bit set.  Therefore, if
    // the top bit is not set, it is because we are using the "same
    // as previous event type" shortcut to save a byte.  Skip back
    // a byte so that we read this byte again.

    if ((event_type & 0x80) == 0)
    {
        event_type = *last_event_type;
        mf->pos--;
    }
    else
    {
        *last_event_type = event_type;
    }

    // Check event type:

    switch (event_type & 0xf0)
    {
        // Two parameter channel events:

    case midi_event_type_t::NOTE_OFF.value():
    case midi_event_type_t::NOTE_ON.value():
    case midi_event_type_t::AFTERTOUCH.value():
    case midi_event_type_t::CONTROLLER.value():
    case midi_event_type_t::PITCH_BEND.value():
        return ReadChannelEvent(event, event_type, true, mf);

        // Single parameter channel events.value():

    case midi_event_type_t::PROGRAM_CHANGE.value():
    case midi_event_type_t::CHAN_AFTERTOUCH.value():
        return ReadChannelEvent(event, event_type, false, mf);

    default:
        break;
    }

    // Specific value?

    switch (event_type)
    {
    case midi_event_type_t::SYSEX.value():
    case midi_event_type_t::SYSEX_SPLIT.value():
        return ReadSysExEvent(event, event_type, mf);

    case midi_event_type_t::META.value():
        return ReadMetaEvent(event, mf);

    default:
        break;
    }

    lprintf(LO_WARN, "ReadEvent: Unknown MIDI event type: 0x%x\n", event_type);
    return false;
}

// Free an event:

static void FreeEvent(midi_event_t *event)
{
    // Some event types have dynamically allocated buffers assigned
    // to them that must be freed.

    switch (event->event_type.value())
    {
    case midi_event_type_t::SYSEX.value():
    case midi_event_type_t::SYSEX_SPLIT.value():
        free(event->data.sysex().data);
        break;

    case midi_event_type_t::META.value():
        free(event->data.meta().data);
        break;

    default:
        // Nothing to do.
        break;
    }
}

// Read and check the track chunk header

static dboolean ReadTrackHeader(midi_track_t *track, midimem_t *mf)
{
    size_t records_read;
    chunk_header_t chunk_header;

    records_read = ReadMultipleBytes(&chunk_header, sizeof(chunk_header_t), mf);

    if (records_read < 1)
    {
        return false;
    }

    if (!CheckChunkHeader(&chunk_header, TRACK_CHUNK_ID))
    {
        return false;
    }

    track->data_len = ntohl(chunk_header.chunk_size);

    return true;
}

static dboolean ReadTrack(midi_track_t *track, midimem_t *mf)
{
    std::vector<midi_event_t> new_events(track->events.size());
    unsigned int last_event_type;

    track->events = {};

    // Read the header:

    if (!ReadTrackHeader(track, mf))
    {
        return false;
    }

    // Then the events:

    last_event_type = 0;

    for (;;)
    {
        // Read the next event:

        track->events.emplace_back();
        midi_event_t &event = track->events.back();
        if (!ReadEvent(&event, &last_event_type, mf))
        {
            return false;
        }

        // End of track?

        if (event.event_type == midi_event_type_t::META &&
            event.data.meta().type == midi_meta_event_type_t::END_OF_TRACK)
        {
            break;
        }
    }

    return true;
}

static dboolean ReadAllTracks(midi_file_t *file, midimem_t *mf)
{
    unsigned int i;

    // Allocate list of tracks and read each track:

    file->tracks =
        (midi_track_t *)malloc(sizeof(midi_track_t) * file->num_tracks);

    if (file->tracks == nullptr)
    {
        return false;
    }

    memset(file->tracks, 0, sizeof(midi_track_t) * file->num_tracks);

    // Read each track:

    for (i = 0; i < file->num_tracks; ++i)
    {
        if (!ReadTrack(&file->tracks[i], mf))
        {
            return false;
        }
    }

    return true;
}

// Read and check the header chunk.

static dboolean ReadFileHeader(midi_file_t *file, midimem_t *mf)
{
    size_t records_read;
    unsigned int format_type;

    records_read = ReadMultipleBytes(&file->header, sizeof(midi_header_t), mf);

    if (records_read < 1)
    {
        return false;
    }

    if (!CheckChunkHeader(&file->header.chunk_header, HEADER_CHUNK_ID) ||
        ntohl(file->header.chunk_header.chunk_size) != 6)
    {
        lprintf(LO_WARN,
                "ReadFileHeader: Invalid MIDI chunk header! "
                "chunk_size=%ld\n",
                ntohl(file->header.chunk_header.chunk_size));
        return false;
    }

    format_type = ntohs(file->header.format_type);
    file->num_tracks = ntohs(file->header.num_tracks);

    if ((format_type != 0 && format_type != 1) || file->num_tracks < 1)
    {
        lprintf(LO_WARN, "ReadFileHeader: Only type 0/1 "
                         "MIDI files supported!\n");
        return false;
    }
    // NSM
    file->header.time_division = ntohs(file->header.time_division);

    return true;
}

void MIDI_FreeFile(midi_file_t *file)
{
    unsigned i;

    if (file->tracks != nullptr)
    {
        free(file->tracks);
    }

    free(file);
}

midi_file_t *MIDI_LoadFile(midimem_t *mf)
{
    midi_file_t *file;

    file = (midi_file_t *)malloc(sizeof(midi_file_t));

    if (file == nullptr)
    {
        return nullptr;
    }

    file->tracks = nullptr;
    file->num_tracks = 0;
    file->buffer = nullptr;
    file->buffer_size = 0;

    // Read MIDI file header

    if (!ReadFileHeader(file, mf))
    {
        MIDI_FreeFile(file);
        return nullptr;
    }

    // Read all tracks:

    if (!ReadAllTracks(file, mf))
    {
        MIDI_FreeFile(file);
        return nullptr;
    }

    return file;
}

// Get the number of tracks in a MIDI file.

unsigned int MIDI_NumTracks(const midi_file_t *file)
{
    return file->num_tracks;
}

// Start iterating over the events in a track.

midi_track_iter_t *MIDI_IterateTrack(const midi_file_t *file,
                                     unsigned int track)
{
    midi_track_iter_t *iter;

    assert(track < file->num_tracks);

    iter = (midi_track_iter_t *)malloc(sizeof(*iter));
    iter->track = &file->tracks[track];
    iter->position = 0;

    return iter;
}

void MIDI_FreeIterator(midi_track_iter_t *iter)
{
    free(iter);
}

// Get the time until the next MIDI event in a track.

unsigned int MIDI_GetDeltaTime(midi_track_iter_t *iter)
{
    if (iter->position < iter->track->events.size())
    {
        midi_event_t *next_event;

        next_event = &iter->track->events[iter->position];

        return next_event->delta_time;
    }

    return 0;
}

// Get a pointer to the next MIDI event.

int MIDI_GetNextEvent(midi_track_iter_t *iter, midi_event_t **event)
{
    if (iter->position < iter->track->events.size())
    {
        *event = &iter->track->events[iter->position];
        ++iter->position;

        return 1;
    }

    return 0;
}

unsigned int MIDI_GetFileTimeDivision(const midi_file_t *file)
{
    return file->header.time_division;
}

void MIDI_RestartIterator(midi_track_iter_t *iter)
{
    iter->position = 0;
}

static void MIDI_PrintFlatListDBG(const midi_event_t **evs)
{
    const midi_event_t *event;

    while (1)
    {
        event = *evs++;

        if (event->delta_time > 0)
        {
            printf("Delay: %i ticks\n", event->delta_time);
        }

        switch (event->event_type.value())
        {
        case midi_event_type_t::NOTE_OFF.value():
            printf("NOTE_OFF\n");
            break;
        case midi_event_type_t::NOTE_ON.value():
            printf("NOTE_ON\n");
            break;
        case midi_event_type_t::AFTERTOUCH.value():
            printf("AFTERTOUCH\n");
            break;
        case midi_event_type_t::CONTROLLER.value():
            printf("CONTROLLER\n");
            break;
        case midi_event_type_t::PROGRAM_CHANGE.value():
            printf("PROGRAM_CHANGE\n");
            break;
        case midi_event_type_t::CHAN_AFTERTOUCH.value():
            printf("CHAN_AFTERTOUCH\n");
            break;
        case midi_event_type_t::PITCH_BEND.value():
            printf("PITCH_BEND\n");
            break;
        case midi_event_type_t::SYSEX.value():
            printf("SYSEX\n");
            break;
        case midi_event_type_t::SYSEX_SPLIT.value():
            printf("SYSEX_SPLIT\n");
            break;
        case midi_event_type_t::META.value():
            printf("META\n");
            break;

        default:
            printf("(unknown)\n");
            break;
        }
        switch (event->event_type.value())
        {
        case midi_event_type_t::NOTE_OFF.value():
        case midi_event_type_t::NOTE_ON.value():
        case midi_event_type_t::AFTERTOUCH.value():
        case midi_event_type_t::CONTROLLER.value():
        case midi_event_type_t::PROGRAM_CHANGE.value():
        case midi_event_type_t::CHAN_AFTERTOUCH.value():
        case midi_event_type_t::PITCH_BEND.value():
            printf("\tChannel: %i\n", event->data.channel().channel);
            printf("\tParameter 1: %i\n", event->data.channel().param1);
            printf("\tParameter 2: %i\n", event->data.channel().param2);
            break;

        case midi_event_type_t::SYSEX.value():
        case midi_event_type_t::SYSEX_SPLIT.value():
            printf("\tLength: %i\n", event->data.sysex().length);
            break;

        case midi_event_type_t::META.value():
            printf("\tMeta type: %i\n", event->data.meta().type.value());
            printf("\tLength: %i\n", event->data.meta().length);
            break;
        }
        if (event->event_type == midi_event_type_t::META &&
            event->data.meta().type == midi_meta_event_type_t::END_OF_TRACK)
        {
            printf("gotta go!\n");
            return;
        }
    }
}

// NSM: an alternate iterator tool.

midi_event_t **MIDI_GenerateFlatList(midi_file_t *file)
{
    int totalevents = 0;
    unsigned i, delta;
    int nextrk;

    int totaldelta = 0;

    int *trackpos = (int *)std::calloc(file->num_tracks, sizeof(int));
    int *tracktime = (int *)std::calloc(file->num_tracks, sizeof(int));
    int trackactive = file->num_tracks;

    midi_event_t **ret;
    midi_event_t **epos;

    for (i = 0; i < file->num_tracks; i++)
    {
        totalevents += file->tracks[i].events.size();
    }

    ret = (midi_event_t **)malloc(totalevents * sizeof(midi_event_t **));

    epos = ret;

    while (trackactive)
    {
        delta = 0x10000000;
        nextrk = -1;
        for (i = 0; i < file->num_tracks; i++)
        {
            if (trackpos[i] != -1 &&
                file->tracks[i].events[trackpos[i]].delta_time - tracktime[i] <
                    delta)
            {
                delta = file->tracks[i].events[trackpos[i]].delta_time -
                        tracktime[i];
                nextrk = i;
            }
        }
        if (nextrk == -1)
        { // unexpected EOF (not every track got end track)
            break;
        }

        *epos = &file->tracks[nextrk].events[trackpos[nextrk]];

        for (i = 0; i < file->num_tracks; i++)
        {
            if (i == (unsigned)nextrk)
            {
                tracktime[i] = 0;
                trackpos[i]++;
            }
            else
            {
                tracktime[i] += delta;
            }
        }
        // yes, this clobbers the original timecodes
        epos[0]->delta_time = delta;
        totaldelta += delta;

        if (epos[0]->event_type == midi_event_type_t::META &&
            epos[0]->data.meta().type == midi_meta_event_type_t::END_OF_TRACK)
        { // change end of track into no op
            trackactive--;
            trackpos[nextrk] = -1;
            epos[0]->data.meta().type = midi_meta_event_type_t::TEXT;
        }
        else if (static_cast<unsigned int>(trackpos[nextrk]) ==
                 file->tracks[nextrk].events.size())
        {
            lprintf(LO_WARN,
                    "MIDI_GenerateFlatList: Unexpected end of track\n");
            std::free(trackpos);
            std::free(tracktime);
            std::free(ret);
            return nullptr;
        }
        epos++;
    }

    if (trackactive)
    { // unexpected EOF
        lprintf(LO_WARN,
                "MIDI_GenerateFlatList: Unexpected end of midi file\n");
        std::free(trackpos);
        std::free(tracktime);
        std::free(ret);
        return nullptr;
    }

    // last end of track event is preserved though
    epos[-1]->data.meta().type = midi_meta_event_type_t::END_OF_TRACK;

    std::free(trackpos);
    std::free(tracktime);

    if (totaldelta < 100)
    {
        lprintf(LO_WARN, "MIDI_GeneratFlatList: very short file %i\n",
                totaldelta);
        free(ret);
        return nullptr;
    }

    // MIDI_PrintFlatListDBG (ret);

    return ret;
}

void MIDI_DestroyFlatList(midi_event_t **evs)
{
    free(evs);
}

// NSM: timing assist functions
// they compute samples per midi clock, where midi clock is the units
// that the time deltas are in, and samples is an arbitrary unit of which
// "sndrate" of them occur per second

static double compute_spmc_normal(unsigned mpq, unsigned tempo,
                                  unsigned sndrate)
{ // returns samples per midi clock

    // inputs: mpq (midi clocks per quarternote, from header)
    // tempo (from tempo event, in microseconds per quarternote)
    // sndrate (sound sample rate in hz)

    // samples   quarternote     microsec    samples    second
    // ------- = ----------- * ----------- * ------- * --------
    // midiclk     midiclk     quarternote   second    microsec

    // return  =  (1 / mpq)  *    tempo    * sndrate * (1 / 1000000)

    return (double)tempo / 1000000 * sndrate / mpq;
}

static double compute_spmc_smpte(unsigned smpte_fps, unsigned mpf,
                                 unsigned sndrate)
{ // returns samples per midi clock

    // inputs: smpte_fps (24, 25, 29, 30)
    // mpf (midi clocks per frame, 0-255)
    // sndrate (sound sample rate in hz)

    // tempo is ignored here

    // samples     frame      seconds    samples
    // ------- = --------- * --------- * -------
    // midiclk    midiclk      frame     second

    // return  = (1 / mpf) * (1 / fps) * sndrate

    double fps; // actual frames per second
    switch (smpte_fps)
    {
    case 24:
    case 25:
    case 30:
        fps = smpte_fps;
        break;
    case 29:
        // i hate NTSC, i really do
        fps = smpte_fps * 1000.0 / 1001.0;
        break;
    default:
        lprintf(LO_WARN, "MIDI_spmc: Unexpected SMPTE timestamp %i\n",
                smpte_fps);
        // assume
        fps = 30.0;
        break;
    }

    return (double)sndrate / fps / mpf;
}

// if event is nullptr, compute with default starting tempo (120BPM)

double MIDI_spmc(const midi_file_t *file, const midi_event_t *ev,
                 unsigned sndrate)
{
    int smpte_fps;
    unsigned tempo;
    unsigned headerval = MIDI_GetFileTimeDivision(file);

    if (headerval & 0x8000) // SMPTE
    {                       // i don't really have any files to test this on...
        smpte_fps = -(short)headerval >> 8;
        return compute_spmc_smpte(smpte_fps, headerval & 0xff, sndrate);
    }

    // normal timing
    tempo = 500000; // default 120BPM
    if (ev)
    {
        if (ev->event_type == midi_event_type_t::META)
        {
            if (ev->data.meta().length == 3)
            {
                tempo = (unsigned)ev->data.meta().data[0] << 16 |
                        (unsigned)ev->data.meta().data[1] << 8 |
                        (unsigned)ev->data.meta().data[2];
            }
            else
            {
                lprintf(LO_WARN, "MIDI_spmc: wrong length tempo meta message "
                                 "in midi file\n");
            }
        }
        else
        {
            lprintf(LO_WARN, "MIDI_spmc: passed non-meta event\n");
        }
    }

    return compute_spmc_normal(headerval, tempo, sndrate);
}

/*
The timing system used by the OPL driver is very interesting. But there are too
many edge cases in multitrack (type 1) midi tempo changes that it simply can't
handle without a major rework. The alternative is that we recook the file into a
single track file with no tempo changes at load time.
*/

midi_file_t *MIDI_LoadFileSpecial(midimem_t *mf)
{
    midi_event_t **flatlist;
    midi_file_t *base = MIDI_LoadFile(mf);
    midi_file_t *ret;

    double opi;

    int epos = 0;

    if (!base)
    {
        return nullptr;
    }

    flatlist = MIDI_GenerateFlatList(base);
    if (!flatlist)
    {
        MIDI_FreeFile(base);
        return nullptr;
    }

    ret = (midi_file_t *)malloc(sizeof(midi_file_t));

    ret->header.format_type = 0;
    ret->header.num_tracks = 1;
    ret->header.time_division = 10000;
    ret->num_tracks = 1;
    ret->buffer_size = 0;
    ret->buffer = nullptr;
    ret->tracks = (midi_track_t *)malloc(sizeof(midi_track_t));

    ret->tracks->events = {};

    opi = MIDI_spmc(base, nullptr, 20000);

    while (1)
    {
        midi_event_t *oldev;

        oldev = flatlist[epos];
        ret->tracks->events.emplace_back();
        midi_event_t &nextev = ret->tracks->events.back();

        // figure delta time
        nextev.delta_time = static_cast<unsigned int>(opi * oldev->delta_time);

        if (oldev->event_type == midi_event_type_t::SYSEX ||
            oldev->event_type == midi_event_type_t::SYSEX_SPLIT)
        // opl player can't process any sysex...
        {
            epos++;
            continue;
        }

        if (oldev->event_type == midi_event_type_t::META)
        {
            if (oldev->data.meta().type == midi_meta_event_type_t::SET_TEMPO)
            { // adjust future tempo scaling
                opi = MIDI_spmc(base, oldev, 20000);
                // insert event as dummy
                nextev.event_type = midi_event_type_t::META;
                nextev.data.meta().type = midi_meta_event_type_t::TEXT;
                nextev.data.meta().length = 0;
                nextev.data.meta().data = (byte *)malloc(4);
                epos++;
                continue;
            }
            if (oldev->data.meta().type == midi_meta_event_type_t::END_OF_TRACK)
            { // reproduce event and break
                nextev.event_type = midi_event_type_t::META;
                nextev.data.meta().type = midi_meta_event_type_t::END_OF_TRACK;
                nextev.data.meta().length = 0;
                nextev.data.meta().data = (byte *)malloc(4);
                epos++;
                break;
            }
            // other meta events not needed
            epos++;
            continue;
        }
        // non meta events can simply be copied (excluding delta time)
        memcpy(&nextev.event_type, &oldev->event_type,
               sizeof(midi_event_t) - sizeof(unsigned));
        epos++;
    }

    MIDI_DestroyFlatList(flatlist);
    MIDI_FreeFile(base);
    return ret;
}

#ifdef TEST

static char *MIDI_EventTypeToString(midi_event_type_t event_type)
{
    switch (event_type)
    {
    case NOTE_OFF:
        return "NOTE_OFF";
    case NOTE_ON:
        return "NOTE_ON";
    case AFTERTOUCH:
        return "AFTERTOUCH";
    case CONTROLLER:
        return "CONTROLLER";
    case PROGRAM_CHANGE:
        return "PROGRAM_CHANGE";
    case CHAN_AFTERTOUCH:
        return "CHAN_AFTERTOUCH";
    case PITCH_BEND:
        return "PITCH_BEND";
    case SYSEX:
        return "SYSEX";
    case SYSEX_SPLIT:
        return "SYSEX_SPLIT";
    case META:
        return "META";

    default:
        return "(unknown)";
    }
}

void PrintTrack(midi_track_t *track)
{
    midi_event_t *event;
    unsigned int i;

    for (i = 0; i < track->num_events; ++i)
    {
        event = &track->events[i];

        if (event->delta_time > 0)
        {
            printf("Delay: %i ticks\n", event->delta_time);
        }

        printf("Event type: %s (%i)\n",
               MIDI_EventTypeToString(event->event_type), event->event_type);

        switch (event->event_type)
        {
        case NOTE_OFF:
        case NOTE_ON:
        case AFTERTOUCH:
        case CONTROLLER:
        case PROGRAM_CHANGE:
        case CHAN_AFTERTOUCH:
        case PITCH_BEND:
            printf("\tChannel: %i\n", event->data.channel.channel);
            printf("\tParameter 1: %i\n", event->data.channel.param1);
            printf("\tParameter 2: %i\n", event->data.channel.param2);
            break;

        case SYSEX:
        case SYSEX_SPLIT:
            printf("\tLength: %i\n", event->data.sysex.length);
            break;

        case META:
            printf("\tMeta type: %i\n", event->data.meta.type);
            printf("\tLength: %i\n", event->data.meta.length);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *f;
    midimem_t mf;
    midi_file_t *file;
    unsigned int i;

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }
    f = fopen(argv[1], "rb");
    if (!f)
    {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    mf.len = ftell(f);
    mf.pos = 0;
    rewind(f);
    mf.data = malloc(mf.len);
    fread(mf.data, 1, mf.len, f);
    fclose(f);

    file = MIDI_LoadFile(&mf);

    if (file == nullptr)
    {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        exit(1);
    }

    for (i = 0; i < file->num_tracks; ++i)
    {
        printf("\n== Track %i ==\n\n", i);

        PrintTrack(&file->tracks[i]);
    }

    return 0;
}

#endif
