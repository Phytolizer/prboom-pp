#pragma once
#include <cstdint>
#include "../smart_enum.hh"
namespace packet_type_e
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
constexpr Type PKT_INIT{0};
constexpr Type PKT_SETUP{1};
constexpr Type PKT_GO{2};
constexpr Type PKT_TICC{3};
constexpr Type PKT_TICS{4};
constexpr Type PKT_RETRANS{5};
constexpr Type PKT_EXTRA{6};
constexpr Type PKT_QUIT{7};
constexpr Type PKT_DOWN{8};
constexpr Type PKT_WAD{9};
constexpr Type PKT_BACKOFF{10};
} // namespace packet_type_e