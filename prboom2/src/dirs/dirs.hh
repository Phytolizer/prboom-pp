#pragma once
#include <array>
#include <cstdint>
#include <string>

namespace rust
{
inline namespace cxxbridge1
{
// #include "rust/cxx.h"

struct unsafe_bitcopy_t;

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final
{
  public:
    String() noexcept;
    String(const String &) noexcept;
    String(String &&) noexcept;
    ~String() noexcept;

    String(const std::string &);
    String(const char *);
    String(const char *, std::size_t);

    String &operator=(const String &) &noexcept;
    String &operator=(String &&) &noexcept;

    explicit operator std::string() const;

    const char *data() const noexcept;
    std::size_t size() const noexcept;
    std::size_t length() const noexcept;

    const char *c_str() noexcept;

    using iterator = char *;
    iterator begin() noexcept;
    iterator end() noexcept;

    using const_iterator = const char *;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    bool operator==(const String &) const noexcept;
    bool operator!=(const String &) const noexcept;
    bool operator<(const String &) const noexcept;
    bool operator<=(const String &) const noexcept;
    bool operator>(const String &) const noexcept;
    bool operator>=(const String &) const noexcept;

    void swap(String &) noexcept;

    String(unsafe_bitcopy_t, const String &) noexcept;

  private:
    friend void swap(String &lhs, String &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING
} // namespace cxxbridge1
} // namespace rust

namespace rust
{
namespace dirs
{
::rust::String get_config_dir() noexcept;
} // namespace dirs
} // namespace rust
