#pragma once
#include "cpp/enums/midi_meta_event_type_t.hh"
#include "doomtype.hh"

struct midi_meta_event_data_t
{
    // Meta event type:

    midi_meta_event_type_t::Type type{midi_meta_event_type_t::END_OF_TRACK};

    // Length:

    unsigned int length{0};

    // Meta event data:

    byte *data{nullptr};

    constexpr bool operator==(const midi_meta_event_data_t &other) const
    {
        return type == other.type && length == other.length &&
               data == other.data;
    }
};

struct midi_sysex_event_data_t
{
    // Length:

    unsigned int length = 0;

    // Event data:

    byte *data = nullptr;

    constexpr bool operator==(const midi_sysex_event_data_t &other) const
    {
        return length == other.length && data == other.data;
    }
};

struct midi_channel_event_data_t
{
    // The channel number to which this applies:

    unsigned int channel = 0;

    // Extra parameters:

    unsigned int param1 = 0;
    unsigned int param2 = 0;

    constexpr bool operator==(const midi_channel_event_data_t &other) const
    {
        return channel == other.channel && param1 == other.param1 &&
               param2 == other.param2;
    }
};