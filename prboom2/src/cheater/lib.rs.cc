#include "cheater/../m_argv.hh"
#include "cheater/../m_cheat.hh"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <new>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace rust
{
inline namespace cxxbridge1
{
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_PANIC
#define CXXBRIDGE1_PANIC
template <typename Exception> void panic [[noreturn]] (const char *msg);
#endif // CXXBRIDGE1_PANIC

namespace
{
template <typename T> class impl;
} // namespace

class Opaque;

template <typename T>::std::size_t size_of();
template <typename T>::std::size_t align_of();

#ifndef CXXBRIDGE1_RUST_SLICE
#define CXXBRIDGE1_RUST_SLICE
namespace detail
{
template <bool> struct copy_assignable_if
{
};

template <> struct copy_assignable_if<false>
{
    copy_assignable_if() noexcept = default;
    copy_assignable_if(const copy_assignable_if &) noexcept = default;
    copy_assignable_if &operator=(const copy_assignable_if &) &noexcept =
        delete;
    copy_assignable_if &operator=(copy_assignable_if &&) &noexcept = default;
};
} // namespace detail

template <typename T>
class Slice final : private detail::copy_assignable_if<std::is_const<T>::value>
{
  public:
    using value_type = T;

    Slice() noexcept;
    Slice(T *, std::size_t count) noexcept;

    Slice &operator=(const Slice<T> &) &noexcept = default;
    Slice &operator=(Slice<T> &&) &noexcept = default;

    T *data() const noexcept;
    std::size_t size() const noexcept;
    std::size_t length() const noexcept;
    bool empty() const noexcept;

    T &operator[](std::size_t n) const noexcept;
    T &at(std::size_t n) const;
    T &front() const noexcept;
    T &back() const noexcept;

    Slice(const Slice<T> &) noexcept = default;
    ~Slice() noexcept = default;

    class iterator;
    iterator begin() const noexcept;
    iterator end() const noexcept;

    void swap(Slice &) noexcept;

  private:
    class uninit;
    Slice(uninit) noexcept;
    friend impl<Slice>;
    friend void sliceInit(void *, const void *, std::size_t) noexcept;
    friend void *slicePtr(const void *) noexcept;
    friend std::size_t sliceLen(const void *) noexcept;

    std::array<std::uintptr_t, 2> repr;
};

template <typename T> class Slice<T>::iterator final
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::add_pointer<T>::type;
    using reference = typename std::add_lvalue_reference<T>::type;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    reference operator[](difference_type) const noexcept;

    iterator &operator++() noexcept;
    iterator operator++(int) noexcept;
    iterator &operator--() noexcept;
    iterator operator--(int) noexcept;

    iterator &operator+=(difference_type) noexcept;
    iterator &operator-=(difference_type) noexcept;
    iterator operator+(difference_type) const noexcept;
    iterator operator-(difference_type) const noexcept;
    difference_type operator-(const iterator &) const noexcept;

    bool operator==(const iterator &) const noexcept;
    bool operator!=(const iterator &) const noexcept;
    bool operator<(const iterator &) const noexcept;
    bool operator<=(const iterator &) const noexcept;
    bool operator>(const iterator &) const noexcept;
    bool operator>=(const iterator &) const noexcept;

  private:
    friend class Slice;
    void *pos;
    std::size_t stride;
};

template <typename T> Slice<T>::Slice() noexcept
{
    sliceInit(this, reinterpret_cast<void *>(align_of<T>()), 0);
}

template <typename T> Slice<T>::Slice(T *s, std::size_t count) noexcept
{
    assert(s != nullptr || count == 0);
    sliceInit(this,
              s == nullptr && count == 0
                  ? reinterpret_cast<void *>(align_of<T>())
                  : const_cast<typename std::remove_const<T>::type *>(s),
              count);
}

template <typename T> T *Slice<T>::data() const noexcept
{
    return reinterpret_cast<T *>(slicePtr(this));
}

template <typename T> std::size_t Slice<T>::size() const noexcept
{
    return sliceLen(this);
}

template <typename T> std::size_t Slice<T>::length() const noexcept
{
    return this->size();
}

template <typename T> bool Slice<T>::empty() const noexcept
{
    return this->size() == 0;
}

template <typename T> T &Slice<T>::operator[](std::size_t n) const noexcept
{
    assert(n < this->size());
    auto pos = static_cast<char *>(slicePtr(this)) + size_of<T>() * n;
    return *reinterpret_cast<T *>(pos);
}

template <typename T> T &Slice<T>::at(std::size_t n) const
{
    if (n >= this->size())
    {
        panic<std::out_of_range>("rust::Slice index out of range");
    }
    return (*this)[n];
}

template <typename T> T &Slice<T>::front() const noexcept
{
    assert(!this->empty());
    return (*this)[0];
}

template <typename T> T &Slice<T>::back() const noexcept
{
    assert(!this->empty());
    return (*this)[this->size() - 1];
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator*()
    const noexcept
{
    return *static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::pointer Slice<T>::iterator::operator->()
    const noexcept
{
    return static_cast<T *>(this->pos);
}

template <typename T>
typename Slice<T>::iterator::reference Slice<T>::iterator::operator[](
    typename Slice<T>::iterator::difference_type n) const noexcept
{
    auto pos = static_cast<char *>(this->pos) + this->stride * n;
    return *reinterpret_cast<T *>(pos);
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator++() noexcept
{
    this->pos = static_cast<char *>(this->pos) + this->stride;
    return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator++(int) noexcept
{
    auto ret = iterator(*this);
    this->pos = static_cast<char *>(this->pos) + this->stride;
    return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator--() noexcept
{
    this->pos = static_cast<char *>(this->pos) - this->stride;
    return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator--(int) noexcept
{
    auto ret = iterator(*this);
    this->pos = static_cast<char *>(this->pos) - this->stride;
    return ret;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator+=(
    typename Slice<T>::iterator::difference_type n) noexcept
{
    this->pos = static_cast<char *>(this->pos) + this->stride * n;
    return *this;
}

template <typename T>
typename Slice<T>::iterator &Slice<T>::iterator::operator-=(
    typename Slice<T>::iterator::difference_type n) noexcept
{
    this->pos = static_cast<char *>(this->pos) - this->stride * n;
    return *this;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator+(
    typename Slice<T>::iterator::difference_type n) const noexcept
{
    auto ret = iterator(*this);
    ret.pos = static_cast<char *>(this->pos) + this->stride * n;
    return ret;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::iterator::operator-(
    typename Slice<T>::iterator::difference_type n) const noexcept
{
    auto ret = iterator(*this);
    ret.pos = static_cast<char *>(this->pos) - this->stride * n;
    return ret;
}

template <typename T>
typename Slice<T>::iterator::difference_type Slice<T>::iterator::operator-(
    const iterator &other) const noexcept
{
    auto diff = std::distance(static_cast<char *>(other.pos),
                              static_cast<char *>(this->pos));
    return diff / this->stride;
}

template <typename T>
bool Slice<T>::iterator::operator==(const iterator &other) const noexcept
{
    return this->pos == other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator!=(const iterator &other) const noexcept
{
    return this->pos != other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<(const iterator &other) const noexcept
{
    return this->pos < other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator<=(const iterator &other) const noexcept
{
    return this->pos <= other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>(const iterator &other) const noexcept
{
    return this->pos > other.pos;
}

template <typename T>
bool Slice<T>::iterator::operator>=(const iterator &other) const noexcept
{
    return this->pos >= other.pos;
}

template <typename T>
typename Slice<T>::iterator Slice<T>::begin() const noexcept
{
    iterator it;
    it.pos = slicePtr(this);
    it.stride = size_of<T>();
    return it;
}

template <typename T> typename Slice<T>::iterator Slice<T>::end() const noexcept
{
    iterator it = this->begin();
    it.pos = static_cast<char *>(it.pos) + it.stride * this->size();
    return it;
}

template <typename T> void Slice<T>::swap(Slice &rhs) noexcept
{
    std::swap(*this, rhs);
}
#endif // CXXBRIDGE1_RUST_SLICE

#ifndef CXXBRIDGE1_RUST_BITCOPY_T
#define CXXBRIDGE1_RUST_BITCOPY_T
struct unsafe_bitcopy_t final
{
    explicit unsafe_bitcopy_t() = default;
};
#endif // CXXBRIDGE1_RUST_BITCOPY_T

#ifndef CXXBRIDGE1_RUST_VEC
#define CXXBRIDGE1_RUST_VEC
template <typename T> class Vec final
{
  public:
    using value_type = T;

    Vec() noexcept;
    Vec(std::initializer_list<T>);
    Vec(const Vec &);
    Vec(Vec &&) noexcept;
    ~Vec() noexcept;

    Vec &operator=(Vec &&) &noexcept;
    Vec &operator=(const Vec &) &;

    std::size_t size() const noexcept;
    bool empty() const noexcept;
    const T *data() const noexcept;
    T *data() noexcept;
    std::size_t capacity() const noexcept;

    const T &operator[](std::size_t n) const noexcept;
    const T &at(std::size_t n) const;
    const T &front() const noexcept;
    const T &back() const noexcept;

    T &operator[](std::size_t n) noexcept;
    T &at(std::size_t n);
    T &front() noexcept;
    T &back() noexcept;

    void reserve(std::size_t new_cap);
    void push_back(const T &value);
    void push_back(T &&value);
    template <typename... Args> void emplace_back(Args &&...args);

    using iterator = typename Slice<T>::iterator;
    iterator begin() noexcept;
    iterator end() noexcept;

    using const_iterator = typename Slice<const T>::iterator;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    void swap(Vec &) noexcept;

    Vec(unsafe_bitcopy_t, const Vec &) noexcept;

  private:
    void reserve_total(std::size_t cap) noexcept;
    void set_len(std::size_t len) noexcept;
    void drop() noexcept;

    friend void swap(Vec &lhs, Vec &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    std::array<std::uintptr_t, 3> repr;
};

template <typename T> Vec<T>::Vec(std::initializer_list<T> init) : Vec{}
{
    this->reserve_total(init.size());
    std::move(init.begin(), init.end(), std::back_inserter(*this));
}

template <typename T> Vec<T>::Vec(const Vec &other) : Vec()
{
    this->reserve_total(other.size());
    std::copy(other.begin(), other.end(), std::back_inserter(*this));
}

template <typename T> Vec<T>::Vec(Vec &&other) noexcept : repr(other.repr)
{
    new (&other) Vec();
}

template <typename T> Vec<T>::~Vec() noexcept
{
    this->drop();
}

template <typename T> Vec<T> &Vec<T>::operator=(Vec &&other) &noexcept
{
    this->drop();
    this->repr = other.repr;
    new (&other) Vec();
    return *this;
}

template <typename T> Vec<T> &Vec<T>::operator=(const Vec &other) &
{
    if (this != &other)
    {
        this->drop();
        new (this) Vec(other);
    }
    return *this;
}

template <typename T> bool Vec<T>::empty() const noexcept
{
    return this->size() == 0;
}

template <typename T> T *Vec<T>::data() noexcept
{
    return const_cast<T *>(const_cast<const Vec<T> *>(this)->data());
}

template <typename T> const T &Vec<T>::operator[](std::size_t n) const noexcept
{
    assert(n < this->size());
    auto data = reinterpret_cast<const char *>(this->data());
    return *reinterpret_cast<const T *>(data + n * size_of<T>());
}

template <typename T> const T &Vec<T>::at(std::size_t n) const
{
    if (n >= this->size())
    {
        panic<std::out_of_range>("rust::Vec index out of range");
    }
    return (*this)[n];
}

template <typename T> const T &Vec<T>::front() const noexcept
{
    assert(!this->empty());
    return (*this)[0];
}

template <typename T> const T &Vec<T>::back() const noexcept
{
    assert(!this->empty());
    return (*this)[this->size() - 1];
}

template <typename T> T &Vec<T>::operator[](std::size_t n) noexcept
{
    assert(n < this->size());
    auto data = reinterpret_cast<char *>(this->data());
    return *reinterpret_cast<T *>(data + n * size_of<T>());
}

template <typename T> T &Vec<T>::at(std::size_t n)
{
    if (n >= this->size())
    {
        panic<std::out_of_range>("rust::Vec index out of range");
    }
    return (*this)[n];
}

template <typename T> T &Vec<T>::front() noexcept
{
    assert(!this->empty());
    return (*this)[0];
}

template <typename T> T &Vec<T>::back() noexcept
{
    assert(!this->empty());
    return (*this)[this->size() - 1];
}

template <typename T> void Vec<T>::reserve(std::size_t new_cap)
{
    this->reserve_total(new_cap);
}

template <typename T> void Vec<T>::push_back(const T &value)
{
    this->emplace_back(value);
}

template <typename T> void Vec<T>::push_back(T &&value)
{
    this->emplace_back(std::move(value));
}

template <typename T>
template <typename... Args>
void Vec<T>::emplace_back(Args &&...args)
{
    auto size = this->size();
    this->reserve_total(size + 1);
    ::new (reinterpret_cast<T *>(reinterpret_cast<char *>(this->data()) +
                                 size * size_of<T>()))
        T(std::forward<Args>(args)...);
    this->set_len(size + 1);
}

template <typename T> typename Vec<T>::iterator Vec<T>::begin() noexcept
{
    return Slice<T>(this->data(), this->size()).begin();
}

template <typename T> typename Vec<T>::iterator Vec<T>::end() noexcept
{
    return Slice<T>(this->data(), this->size()).end();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::begin() const noexcept
{
    return this->cbegin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::end() const noexcept
{
    return this->cend();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cbegin() const noexcept
{
    return Slice<const T>(this->data(), this->size()).begin();
}

template <typename T>
typename Vec<T>::const_iterator Vec<T>::cend() const noexcept
{
    return Slice<const T>(this->data(), this->size()).end();
}

template <typename T> void Vec<T>::swap(Vec &rhs) noexcept
{
    using std::swap;
    swap(this->repr, rhs.repr);
}

template <typename T>
Vec<T>::Vec(unsafe_bitcopy_t, const Vec &bits) noexcept : repr(bits.repr)
{
}
#endif // CXXBRIDGE1_RUST_VEC

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail
{
namespace
{
template <typename T, typename = std::size_t>
struct is_complete : std::false_type
{
};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type
{
};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout
{
    template <typename T> friend std::size_t size_of();
    template <typename T> friend std::size_t align_of();
    template <typename T>
    static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                   std::size_t>::type
    do_size_of()
    {
        return T::layout::size();
    }
    template <typename T>
    static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                   std::size_t>::type
    do_size_of()
    {
        return sizeof(T);
    }
    template <typename T>
    static typename std::enable_if<detail::is_complete<T>::value,
                                   std::size_t>::type
    size_of()
    {
        return do_size_of<T>();
    }
    template <typename T>
    static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                   std::size_t>::type
    do_align_of()
    {
        return T::layout::align();
    }
    template <typename T>
    static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                   std::size_t>::type
    do_align_of()
    {
        return alignof(T);
    }
    template <typename T>
    static typename std::enable_if<detail::is_complete<T>::value,
                                   std::size_t>::type
    align_of()
    {
        return do_align_of<T>();
    }
};

template <typename T> std::size_t size_of()
{
    return layout::size_of<T>();
}

template <typename T> std::size_t align_of()
{
    return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT

namespace detail
{
template <typename T, typename = void *> struct operator_new
{
    void *operator()(::std::size_t sz)
    {
        return ::operator new(sz);
    }
};

template <typename T>
struct operator_new<T, decltype(T::operator new(sizeof(T)))>
{
    void *operator()(::std::size_t sz)
    {
        return T::operator new(sz);
    }
};
} // namespace detail

template <typename T> union MaybeUninit {
    T value;
    void *operator new(::std::size_t sz)
    {
        return detail::operator_new<T>{}(sz);
    }
    MaybeUninit()
    {
    }
    ~MaybeUninit()
    {
    }
};
} // namespace cxxbridge1
} // namespace rust

enum class Cheats : ::std::uint8_t;

#ifndef CXXBRIDGE1_ENUM_Cheats
#define CXXBRIDGE1_ENUM_Cheats
enum class Cheats : ::std::uint8_t
{
    IDMUS = 0,
    IDCHOPPERS = 1,
    IDDQD = 2,
    IDKFA = 3,
    IDFA = 4,
    IDSPISPOPD = 5,
    IDCLIP = 6,
    IDBEHOLDH = 7,
    IDBEHOLDM = 8,
    IDBEHOLDV = 9,
    IDBEHOLDS = 10,
    IDBEHOLDI = 11,
    IDBEHOLDR = 12,
    IDBEHOLDA = 13,
    IDBEHOLDL = 14,
    IDBEHOLD = 15,
    IDCLEV = 16,
    IDMYPOS = 17,
    IDRATE = 18,
    TNTCOMP = 19,
    TNTEM = 20,
    IDDT = 21,
    TNTHOM = 22,
    TNTKEY = 23,
    TNTKEYR = 24,
    TNTKEYY = 25,
    TNTKEYB = 26,
    TNTKEYRC = 27,
    TNTKEYYC = 28,
    TNTKEYBC = 29,
    TNTKEYRS = 30,
    TNTKEYYS = 31,
    TNTKEYBS = 32,
    TNTKA = 33,
    TNTWEAP = 34,
    TNTWEAPX = 35,
    TNTAMMO = 36,
    TNTAMMOX = 37,
    TNTTRAN = 38,
    TNTSMART = 39,
    TNTPITCH = 40,
    TNTRAN = 41,
    TNTAMO = 42,
    TNTAMOX = 43,
    TNTFAST = 44,
    TNTICE = 45,
    TNTPUSH = 46,
    NOTARGET = 47,
    FLY = 48,
    BUDDHA = 49,
};
#endif // CXXBRIDGE1_ENUM_Cheats

namespace rust
{
namespace cheater
{
extern "C"
{
    void rust$cheater$cxxbridge1$start_game(
        ::rust::Vec<::Cheats> *return$) noexcept;
} // extern "C"
} // namespace cheater
} // namespace rust

extern "C"
{
    ::std::int32_t cxxbridge1$M_CheckParm(const ::std::string &parm) noexcept
    {
        ::std::int32_t (*M_CheckParm$)(const ::std::string &) = ::M_CheckParm;
        return M_CheckParm$(parm);
    }

    void cxxbridge1$cheat_god() noexcept
    {
        void (*cheat_god$)() = ::cheat_god;
        cheat_god$();
    }

    void cxxbridge1$cheat_buddha() noexcept
    {
        void (*cheat_buddha$)() = ::cheat_buddha;
        cheat_buddha$();
    }
} // extern "C"

namespace rust
{
namespace cheater
{
::rust::Vec<::Cheats> start_game() noexcept
{
    ::rust::MaybeUninit<::rust::Vec<::Cheats>> return$;
    rust$cheater$cxxbridge1$start_game(&return$.value);
    return ::std::move(return$.value);
}
} // namespace cheater
} // namespace rust

extern "C"
{
    void cxxbridge1$rust_vec$Cheats$new(
        const ::rust::Vec<::Cheats> *ptr) noexcept;
    void cxxbridge1$rust_vec$Cheats$drop(::rust::Vec<::Cheats> *ptr) noexcept;
    ::std::size_t cxxbridge1$rust_vec$Cheats$len(
        const ::rust::Vec<::Cheats> *ptr) noexcept;
    ::std::size_t cxxbridge1$rust_vec$Cheats$capacity(
        const ::rust::Vec<::Cheats> *ptr) noexcept;
    const ::Cheats *cxxbridge1$rust_vec$Cheats$data(
        const ::rust::Vec<::Cheats> *ptr) noexcept;
    void cxxbridge1$rust_vec$Cheats$reserve_total(::rust::Vec<::Cheats> *ptr,
                                                  ::std::size_t cap) noexcept;
    void cxxbridge1$rust_vec$Cheats$set_len(::rust::Vec<::Cheats> *ptr,
                                            ::std::size_t len) noexcept;
} // extern "C"

namespace rust
{
inline namespace cxxbridge1
{
template <> Vec<::Cheats>::Vec() noexcept
{
    cxxbridge1$rust_vec$Cheats$new(this);
}
template <> void Vec<::Cheats>::drop() noexcept
{
    return cxxbridge1$rust_vec$Cheats$drop(this);
}
template <>::std::size_t Vec<::Cheats>::size() const noexcept
{
    return cxxbridge1$rust_vec$Cheats$len(this);
}
template <>::std::size_t Vec<::Cheats>::capacity() const noexcept
{
    return cxxbridge1$rust_vec$Cheats$capacity(this);
}
template <> const ::Cheats *Vec<::Cheats>::data() const noexcept
{
    return cxxbridge1$rust_vec$Cheats$data(this);
}
template <> void Vec<::Cheats>::reserve_total(::std::size_t cap) noexcept
{
    return cxxbridge1$rust_vec$Cheats$reserve_total(this, cap);
}
template <> void Vec<::Cheats>::set_len(::std::size_t len) noexcept
{
    return cxxbridge1$rust_vec$Cheats$set_len(this, len);
}
} // namespace cxxbridge1
} // namespace rust
