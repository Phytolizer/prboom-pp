#pragma once
#include "../smart_enum.hh"
#include <cstdint>
namespace midi_event_type_t
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
constexpr Type NOTE_OFF{0x80};
constexpr Type NOTE_ON{0x90};
constexpr Type AFTERTOUCH{0xa0};
constexpr Type CONTROLLER{0xb0};
constexpr Type PROGRAM_CHANGE{0xc0};
constexpr Type CHAN_AFTERTOUCH{0xd0};
constexpr Type PITCH_BEND{0xe0};
constexpr Type SYSEX{0xf0};
constexpr Type SYSEX_SPLIT{0xf7};
constexpr Type META{0xff};
} // namespace midi_event_type_t