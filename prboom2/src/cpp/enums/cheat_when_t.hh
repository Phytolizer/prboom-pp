#pragma once
#include "../smart_enum.hh"
#include <cstdint>
namespace cheat_when_t
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
constexpr Type always{0};
constexpr Type not_dm{1};
constexpr Type not_coop{2};
constexpr Type not_demo{4};
constexpr Type not_menu{8};
constexpr Type not_deh{16};
constexpr Type not_net{not_dm | not_coop};
constexpr Type cht_never{not_net | not_demo};
} // namespace cheat_when_t