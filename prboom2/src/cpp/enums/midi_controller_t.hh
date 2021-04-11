#pragma once
#include "../smart_enum.hh"
#include <cstdint>
namespace midi_controller_t
{
class Type final : public SmartEnum<uint32_t, Type>
{
  public:
    explicit constexpr Type(uint32_t value) : SmartEnum<uint32_t, Type>(value)
    {
    }
    constexpr Type(SmartEnum<uint32_t, Type> value)
        : SmartEnum<uint32_t, Type>(value.value())
    {
    }
};
constexpr Type BANK_SELECT{0x0};
constexpr Type MODULATION{0x1};
constexpr Type BREATH_CONTROL{0x2};
constexpr Type FOOT_CONTROL{0x3};
constexpr Type PORTAMENTO{0x4};
constexpr Type DATA_ENTRY{0x5};
constexpr Type MAIN_VOLUME{0x7};
constexpr Type PAN{0xa};
} // namespace midi_controller_t