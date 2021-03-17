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
//     MIDI file parsing.
//
//-----------------------------------------------------------------------------

#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <cstddef>

#include "doomtype.hh"
#include "cpp/enums/midi_meta_event_type_t.hh"
#include "cpp/enums/midi_controller_t.hh"
#include "cpp/enums/midi_event_type_t.hh"

struct midi_track_t;

struct chunk_header_t
{
    byte chunk_id[4];
    unsigned int chunk_size;
} PACKEDATTR;

struct midi_header_t
{
    chunk_header_t chunk_header;
    unsigned short format_type;
    unsigned short num_tracks;
    unsigned short time_division;
} PACKEDATTR;

struct midi_track_iter_t
{
    midi_track_t *track;
    unsigned int position;
};

struct midi_file_t
{
    midi_header_t header;

    // All tracks in this file:
    midi_track_t *tracks;
    unsigned int num_tracks;

    // Data buffer used to store data read for SysEx or meta events:
    byte *buffer;
    unsigned int buffer_size;
};

#define MIDI_CHANNELS_PER_TRACK 16

using midimem_t = struct
{
    const byte *data;
    std::size_t len;
    std::size_t pos;
};

struct midi_meta_event_data_t
{
    // Meta event type:

    midi_meta_event_type_t::Type type;

    // Length:

    unsigned int length;

    // Meta event data:

    byte *data;
};

struct midi_sysex_event_data_t
{
    // Length:

    unsigned int length;

    // Event data:

    byte *data;
};

struct midi_channel_event_data_t
{
    // The channel number to which this applies:

    unsigned int channel;

    // Extra parameters:

    unsigned int param1;
    unsigned int param2;
};

struct midi_event_t
{
    // Time between the previous event and this event.
    unsigned int delta_time;

    // Type of event:
    midi_event_type_t::Type event_type;

    union {
        midi_channel_event_data_t channel;
        midi_meta_event_data_t meta;
        midi_sysex_event_data_t sysex;
    } data;
} ;

// Load a MIDI file.

midi_file_t *MIDI_LoadFile(midimem_t *mf);

// Free a MIDI file.

void MIDI_FreeFile(midi_file_t *file);

// Get the time division value from the MIDI header.

unsigned int MIDI_GetFileTimeDivision(const midi_file_t *file);

// Get the number of tracks in a MIDI file.

unsigned int MIDI_NumTracks(const midi_file_t *file);

// Start iterating over the events in a track.

midi_track_iter_t *MIDI_IterateTrack(const midi_file_t *file,
                                     unsigned int track_num);

// Free an iterator.

void MIDI_FreeIterator(midi_track_iter_t *iter);

// Get the time until the next MIDI event in a track.

unsigned int MIDI_GetDeltaTime(midi_track_iter_t *iter);

// Get a pointer to the next MIDI event.

int MIDI_GetNextEvent(midi_track_iter_t *iter, midi_event_t **event);

// Reset an iterator to the beginning of a track.

void MIDI_RestartIterator(midi_track_iter_t *iter);

// NSM: an alternate iterator tool.
midi_event_t **MIDI_GenerateFlatList(midi_file_t *file);
void MIDI_DestroyFlatList(midi_event_t **evs);

// NSM: timing calculator
double MIDI_spmc(const midi_file_t *file, const midi_event_t *ev,
                 unsigned sndrate);

midi_file_t *MIDI_LoadFileSpecial(midimem_t *mf);

#endif /* #ifndef MIDIFILE_H */
