//
// Created by kyle on 3/12/21.
//

#pragma once

template <typename Underlying, class Derived> class SmartEnum
{
    Underlying m_value;

  public:
    constexpr explicit SmartEnum(Underlying value) : m_value(value)
    {
    }

    constexpr Underlying value() const
    {
        return m_value;
    }

    constexpr SmartEnum operator&(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value & other.m_value)};
    }

    constexpr SmartEnum operator|(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value | other.m_value)};
    }

    constexpr SmartEnum operator^(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value ^ other.m_value)};
    }

    constexpr SmartEnum operator~() const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(~m_value)};
    }

    constexpr SmartEnum &operator&=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value &= other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator|=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value |= other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator^=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value ^= other.m_value;
        return *this;
    }

    constexpr SmartEnum operator+(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value + other.m_value)};
    }

    constexpr SmartEnum operator-(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value - other.m_value)};
    }

    constexpr SmartEnum operator*(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value * other.m_value)};
    }

    constexpr SmartEnum operator/(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value / other.m_value)};
    }

    constexpr SmartEnum operator%(const SmartEnum<Underlying, Derived> &other
    ) const
    {
        return SmartEnum<Underlying, Derived>{
            static_cast<Underlying>(m_value % other.m_value)};
    }

    constexpr SmartEnum &operator+=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value += other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator-=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value -= other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator*=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value *= other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator/=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value /= other.m_value;
        return *this;
    }

    constexpr SmartEnum &operator%=(const SmartEnum<Underlying, Derived> &other)
    {
        m_value %= other.m_value;
        return *this;
    }

    constexpr SmartEnum operator++()
    {
        m_value++;
        return *this;
    }

    constexpr SmartEnum operator++(int)
    {
        Underlying old = m_value;
        m_value++;
        return SmartEnum<Underlying, Derived>{old};
    }

    constexpr SmartEnum operator--()
    {
        m_value--;
        return *this;
    }

    constexpr SmartEnum operator--(int)
    {
        Underlying old = m_value;
        m_value--;
        return SmartEnum<Underlying, Derived>{old};
    }

    constexpr bool operator==(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value == other.m_value;
    }

    constexpr bool operator!=(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value != other.m_value;
    }

    constexpr bool operator<(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value < other.m_value;
    }

    constexpr bool operator<=(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value <= other.m_value;
    }

    constexpr bool operator>(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value > other.m_value;
    }

    constexpr bool operator>=(const SmartEnum<Underlying, Derived> &other) const
    {
        return m_value >= other.m_value;
    }

    [[nodiscard]] constexpr bool nonzero() const
    {
        return m_value != 0;
    }

    [[nodiscard]] constexpr bool zero() const
    {
        return m_value == 0;
    }
};
