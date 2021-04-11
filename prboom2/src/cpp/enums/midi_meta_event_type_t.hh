#pragma once
#include "../smart_enum.hh"
#include <cstdint>
namespace midi_meta_event_type_t
{
class Type final : public SmartEnum<uint8_t, Type>
{
  public:
    explicit constexpr Type(uint8_t value) : SmartEnum<uint8_t, Type>(value)
    {
    }
    constexpr Type(SmartEnum<uint8_t, Type> value)
        : SmartEnum<uint8_t, Type>(value.value())
    {
    }
};
constexpr Type SEQUENCE_NUMBER{0x0};
constexpr Type TEXT{0x1};
constexpr Type COPYRIGHT{0x2};
constexpr Type TRACK_NAME{0x3};
constexpr Type INSTR_NAME{0x4};
constexpr Type LYRICS{0x5};
constexpr Type MARKER{0x6};
constexpr Type CUE_POINT{0x7};
constexpr Type CHANNEL_PREFIX{0x20};
constexpr Type END_OF_TRACK{0x2f};
constexpr Type SET_TEMPO{0x51};
constexpr Type SMPTE_OFFSET{0x54};
constexpr Type TIME_SIGNATURE{0x58};
constexpr Type KEY_SIGNATURE{0x59};
constexpr Type SEQUENCER_SPECIFIC{0x7f};
} // namespace midi_meta_event_type_t