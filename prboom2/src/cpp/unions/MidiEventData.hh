#pragma once
#include <cstdint>
#include <stdexcept>
#include "MUSIC/midifile_events.hh"
class MidiEventData
{
    midi_channel_event_data_t m_channel{};
    midi_meta_event_data_t m_meta{};
    midi_sysex_event_data_t m_sysex{};
    enum class D
    {
        channel,
        meta,
        sysex,
        undefined
    };
    D m_d = D::undefined;

  public:
    constexpr MidiEventData() = default;
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr MidiEventData(midi_channel_event_data_t channel)
        : m_channel(channel), m_d(D::channel)
    {
    } // ctor(midi_channel_event_data_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr MidiEventData(midi_meta_event_data_t meta)
        : m_meta(meta), m_d(D::meta)
    {
    } // ctor(midi_meta_event_data_t)
    // NOLINTNEXTLINE(google-explicit-constructor,hicpp-explicit-conversions)
    constexpr MidiEventData(midi_sysex_event_data_t sysex)
        : m_sysex(sysex), m_d(D::sysex)
    {
    } // ctor(midi_sysex_event_data_t)
    [[nodiscard]] constexpr bool isChannel()
    {
        return m_d == D::channel;
    } // fn ischannel
    [[nodiscard]] constexpr const midi_channel_event_data_t &channel() const
    {
        if (m_d == D::channel)
        {
            return m_channel;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_channel_event_data_t'"};
    } // fn channel const
    [[nodiscard]] constexpr midi_channel_event_data_t &channel()
    {
        if (m_d == D::channel)
        {
            return m_channel;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_channel_event_data_t'"};
    } // fn channel
    void setChannel()
    {
        m_d = D::channel;
    } // setChannel
    [[nodiscard]] constexpr bool isMeta()
    {
        return m_d == D::meta;
    } // fn ismeta
    [[nodiscard]] constexpr const midi_meta_event_data_t &meta() const
    {
        if (m_d == D::meta)
        {
            return m_meta;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_meta_event_data_t'"};
    } // fn meta const
    [[nodiscard]] constexpr midi_meta_event_data_t &meta()
    {
        if (m_d == D::meta)
        {
            return m_meta;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_meta_event_data_t'"};
    } // fn meta
    void setMeta()
    {
        m_d = D::meta;
    } // setMeta
    [[nodiscard]] constexpr bool isSysex()
    {
        return m_d == D::sysex;
    } // fn issysex
    [[nodiscard]] constexpr const midi_sysex_event_data_t &sysex() const
    {
        if (m_d == D::sysex)
        {
            return m_sysex;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_sysex_event_data_t'"};
    } // fn sysex const
    [[nodiscard]] constexpr midi_sysex_event_data_t &sysex()
    {
        if (m_d == D::sysex)
        {
            return m_sysex;
        }
        throw std::runtime_error{"in 'MidiEventData.hh': This MidiEventData is "
                                 "not a 'midi_sysex_event_data_t'"};
    } // fn sysex
    void setSysex()
    {
        m_d = D::sysex;
    } // setSysex
    [[nodiscard]] constexpr bool isNull() const
    {
        return m_d == D::undefined;
    } // fn isNull
    [[nodiscard]] constexpr bool notNull() const
    {
        return m_d != D::undefined;
    } // fn notNull
    [[nodiscard]] constexpr bool operator==(const MidiEventData &other) const
    {
        switch (m_d)
        {
        case D::channel:
            return m_d == other.m_d && m_channel == other.m_channel;
        case D::meta:
            return m_d == other.m_d && m_meta == other.m_meta;
        case D::sysex:
            return m_d == other.m_d && m_sysex == other.m_sysex;
        case D::undefined:
            return other.m_d == D::undefined;
        }             // switch (m_d)
        return false; // unreachable
    }                 // fn operator==
    [[nodiscard]] constexpr bool operator!=(const MidiEventData &other) const
    {
        return !(*this == other);
    } // fn operator!=
};