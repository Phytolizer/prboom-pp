#pragma once
#include <cstdint>
#include "../smart_enum.hh"
namespace Token
{
class Type final : public SmartEnum<std::size_t, Type>
{
  public:
    explicit constexpr Type(std::size_t value)
        : SmartEnum<std::size_t, Type>(value)
    {
    }
    constexpr Type(SmartEnum<std::size_t, Type> value)
        : SmartEnum<std::size_t, Type>(value.value())
    {
    }
};
constexpr Type Identifier{0};
constexpr Type StringConst{1};
constexpr Type IntConst{2};
constexpr Type FloatConst{3};
constexpr Type BoolConst{4};
constexpr Type AndAnd{5};
constexpr Type OrOr{6};
constexpr Type EqEq{7};
constexpr Type NotEq{8};
constexpr Type GtrEq{9};
constexpr Type LessEq{10};
constexpr Type ShiftLeft{11};
constexpr Type ShiftRight{12};
constexpr Type NumSpecialTokens{13};
constexpr Type NoToken{14};
} // namespace Token