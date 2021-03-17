#pragma once
#include <cstdint>
#include "../smart_enum.hh"
namespace cheat_when_t
{
class Type final : public SmartEnum<short, Type>
{
  public:
    explicit constexpr Type(short value) : SmartEnum<short, Type>(value)
    {
    }
    constexpr Type(SmartEnum<short, Type> value)
        : SmartEnum<short, Type>(value.value())
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