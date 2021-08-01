// Copyright (c) 2020 nakat-t
// See LICENSE file for license information.
#ifndef utility_cpp11_UTILITY_HPP_
#define utility_cpp11_UTILITY_HPP_

#define utility_cpp11_VERSION_MAJOR 0
#define utility_cpp11_VERSION_MINOR 2
#define utility_cpp11_VERSION_PATCH 0

#define utility_cpp11_STR(v) #v
#define utility_cpp11_VERSION_(major, minor, patch) utility_cpp11_STR(major) "." utility_cpp11_STR(minor) "." utility_cpp11_STR(patch)
#define utility_cpp11_VERSION utility_cpp11_VERSION_(utility_cpp11_VERSION_MAJOR, utility_cpp11_VERSION_MINOR, utility_cpp11_VERSION_PATCH)

#if !defined(utility_cpp11_CPLUSPLUS)
#   if defined(_MSC_VER) && !defined(__clang__)
#       if defined(_MSVC_LANG) // Available beginning in Visual Studio 2015 Update 3
#           define utility_cpp11_CPLUSPLUS _MSVC_LANG
#       elif _MSC_VER == 1900 && _MSC_FULL_VER >= 190023506 // Visual Studio 2015 Update 1
#           define utility_cpp11_CPLUSPLUS 201103L
#       else
#           define utility_cpp11_CPLUSPLUS 199711L
#       endif
#   else
#       define utility_cpp11_CPLUSPLUS __cplusplus
#   endif
#endif // !defined(utility_cpp11_CPLUSPLUS)

#define utility_cpp11_CPP98_OR_LATER (utility_cpp11_CPLUSPLUS >= 199711L)
#define utility_cpp11_CPP11_OR_LATER (utility_cpp11_CPLUSPLUS >= 201103L)
#define utility_cpp11_CPP14_OR_LATER (utility_cpp11_CPLUSPLUS >= 201402L)
#define utility_cpp11_CPP17_OR_LATER (utility_cpp11_CPLUSPLUS >= 201703L)
#define utility_cpp11_CPP20_OR_LATER (utility_cpp11_CPLUSPLUS >= 202002L)

#include <cstddef>
#include <utility>

// Visual Studio 2015 says it supports C++14, but does not implement the C++14 constexpr extension.
#if utility_cpp11_CPP14_OR_LATER
#   if defined(_MSC_VER) && _MSC_VER >= 1915 // Boost says msvc was supported with _MSC_VER >= 1915.
#       define utility_cpp11_HAS_CONSTEXPR14 1
#   elif defined(_MSC_VER) && _MSC_VER == 1900
#       define utility_cpp11_HAS_CONSTEXPR14 0
#   else
#       define utility_cpp11_HAS_CONSTEXPR14 1
#   endif
#else
#   define utility_cpp11_HAS_CONSTEXPR14 0
#endif

#if utility_cpp11_HAS_CONSTEXPR14
#   define utility_cpp11_CONSTEXPR14 constexpr
#else
#   define utility_cpp11_CONSTEXPR14 /*constexpr*/
#endif

#if defined(__cpp_inline_variables)
#   define utility_cpp11_HAS_INLINE_VARIABLES 1
#else
#   define utility_cpp11_HAS_INLINE_VARIABLES 0
#endif

#if defined(__cpp_lib_exchange_function)
#   define utility_cpp11_HAS_EXCHANGE_FUNCTION 1
#else
#   define utility_cpp11_HAS_EXCHANGE_FUNCTION 0
#endif

#if defined(__cpp_lib_constexpr_utility)
#   define utility_cpp11_HAS_CONSTEXPR_UTILITY 1
#else
#   define utility_cpp11_HAS_CONSTEXPR_UTILITY 0
#endif

#if defined(__cpp_lib_as_const)
#   define utility_cpp11_HAS_AS_CONST 1
#else
#   define utility_cpp11_HAS_AS_CONST 0
#   include <type_traits>
#endif

#if defined(__cpp_lib_integer_comparison_functions)
#   define utility_cpp11_HAS_INTEGER_COMPARISON_FUNCTIONS 1
#else
#   define utility_cpp11_HAS_INTEGER_COMPARISON_FUNCTIONS 0
#   include <limits>
#   include <type_traits>
#endif

#if defined(__cpp_lib_integer_sequence)
#   define utility_cpp11_HAS_INTEGER_SEQUENCE 1
#else
#   define utility_cpp11_HAS_INTEGER_SEQUENCE 0
#   include <cstddef>
#   include <type_traits>
#endif

#if utility_cpp11_CPP17_OR_LATER
#   define utility_cpp11_HAS_IN_PLACE 1
#else
#   define utility_cpp11_HAS_IN_PLACE 0
#   include <cstddef>
#endif

namespace utility_cpp11 {

// [utility.exchange]
#if utility_cpp11_HAS_EXCHANGE_FUNCTION && utility_cpp11_HAS_CONSTEXPR_UTILITY
using std::exchange;
#else
template <typename T, typename U = T>
inline utility_cpp11_CONSTEXPR14
T
exchange(T& obj, U&& new_value)
{
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}
#endif // utility_cpp11_HAS_EXCHANGE_FUNCTION && utility_cpp11_HAS_CONSTEXPR_UTILITY

// [utility.as_const]
#if utility_cpp11_HAS_AS_CONST
using std::as_const;
#else
template <typename T>
inline constexpr
typename std::add_const<T>::type&
as_const(T& t) noexcept
{
    return t;
}
template <typename T>
void
as_const(const T&&) = delete;
#endif

// [utility.intcmp]
#if utility_cpp11_HAS_INTEGER_COMPARISON_FUNCTIONS
using std::cmp_equal;
using std::cmp_not_equal;
using std::cmp_less;
using std::cmp_greater;
using std::cmp_less_equal;
using std::cmp_greater_equal;
using std::in_range;
#else

template <
    typename T, typename U,
    typename std::enable_if<
        (std::is_signed<T>::value && std::is_signed<U>::value) || (!std::is_signed<T>::value && !std::is_signed<U>::value), 
        std::nullptr_t
    >::type = nullptr
>
inline constexpr
bool
cmp_equal(T t, U u) noexcept
{
    return t == u;
}

template <
    typename T, typename U,
    typename std::enable_if<std::is_signed<T>::value && !std::is_signed<U>::value, std::nullptr_t>::type = nullptr
>
inline constexpr
bool
cmp_equal(T t, U u) noexcept
{
    using UT = typename std::make_unsigned<T>::type;
    return (t < 0) ? false : UT(t) == u;
}

template <
    typename T, typename U,
    typename std::enable_if<!std::is_signed<T>::value && std::is_signed<U>::value, std::nullptr_t>::type = nullptr
>
inline constexpr
bool
cmp_equal(T t, U u) noexcept
{
    using UU = typename std::make_unsigned<U>::type;
    return (u < 0) ? false : t == UU(u);
}

template <typename T, typename U>
inline constexpr
bool
cmp_not_equal(T t, U u) noexcept
{
    return !utility_cpp11::cmp_equal(t, u);
}

template <
    typename T, typename U,
    typename std::enable_if<
        (std::is_signed<T>::value && std::is_signed<U>::value) || (!std::is_signed<T>::value && !std::is_signed<U>::value), 
        std::nullptr_t
    >::type = nullptr
>
inline constexpr
bool
cmp_less(T t, U u) noexcept
{
    return t < u;
}

template <
    typename T, typename U,
    typename std::enable_if<std::is_signed<T>::value && !std::is_signed<U>::value, std::nullptr_t>::type = nullptr
>
inline constexpr
bool
cmp_less(T t, U u) noexcept
{
    using UT = typename std::make_unsigned<T>::type;
    return (t < 0) ? true : UT(t) < u;
}

template <
    typename T, typename U,
    typename std::enable_if<!std::is_signed<T>::value && std::is_signed<U>::value, std::nullptr_t>::type = nullptr
>
inline constexpr
bool
cmp_less(T t, U u) noexcept
{
    using UU = typename std::make_unsigned<U>::type;
    return (u < 0) ? false : t < UU(u);
}

template <typename T, typename U>
inline constexpr
bool
cmp_greater(T t, U u) noexcept
{
    return utility_cpp11::cmp_less(u, t);
}

template <typename T, typename U>
inline constexpr
bool
cmp_less_equal(T t, U u) noexcept
{
    return !utility_cpp11::cmp_greater(t, u);
}

template <typename T, typename U>
inline constexpr
bool
cmp_greater_equal(T t, U u) noexcept
{
    return !utility_cpp11::cmp_less(t, u);
}

template<typename R, typename T>
inline constexpr
bool
in_range(T t) noexcept
{
    return utility_cpp11::cmp_greater_equal(t, std::numeric_limits<R>::min()) && utility_cpp11::cmp_less_equal(t, std::numeric_limits<R>::max());
}

#endif // utility_cpp11_HAS_INTEGER_COMPARISON_FUNCTIONS

#if utility_cpp11_HAS_INTEGER_SEQUENCE

using std::integer_sequence;
using std::index_sequence;
using std::make_integer_sequence;
using std::make_index_sequence;
using std::index_sequence_for;

#else // utility_cpp11_HAS_INTEGER_SEQUENCE

template <typename T, T... Ints>
struct integer_sequence
{
    static_assert(std::is_integral<T>::value, "integer_sequence can only be instantiated with an integral type");

    using value_type = T;
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
};

template <std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

namespace utility_cpp11_detail {

template <typename Seq, std::size_t N, std::size_t Rem>
struct concat;

template <typename T, T... Ints, std::size_t N>
struct concat<integer_sequence<T, Ints...>, N, 0> {
    using type = integer_sequence<T, Ints..., (Ints + N)...>;
};

template <typename T, T... Ints, size_t N>
struct concat<integer_sequence<T, Ints...>, N, 1> {
    using type = integer_sequence<T, Ints..., (Ints + N)..., 2 * N>;
};

template <typename T, std::size_t N>
struct gen_seq {
    using type = typename concat<typename gen_seq<T, N / 2>::type, N / 2, N % 2>::type;
};

template <typename T>
struct gen_seq<T, 0> {
    using type = integer_sequence<T>;
};

template <typename T, T N>
struct gen_seq_checked
{
    static_assert(0 <= N, "make_integer_sequence must have a non-negative sequence length");
    using type = typename gen_seq<T, 0 <= N ? N : 0>::type;
};

} // namespace utility_cpp11_detail

template<typename T, T N>
using make_integer_sequence = typename utility_cpp11_detail::gen_seq_checked<T, N>::type;

template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template<typename... T>
using index_sequence_for = make_index_sequence<sizeof...(T)>;

#endif // utility_cpp11_HAS_INTEGER_SEQUENCE

// in-place construction
#if utility_cpp11_HAS_IN_PLACE

using std::in_place;
using std::in_place_type;
using std::in_place_index;
using std::in_place_t;
using std::in_place_type_t;
using std::in_place_index_t;

#define utility_cpp11_in_place          (std::in_place)
#define utility_cpp11_in_place_type(T)  (std::in_place_type<T>)
#define utility_cpp11_in_place_index(I) (std::in_place_index<I>)

#else // utility_cpp11_HAS_IN_PLACE

struct in_place_t {
    explicit in_place_t() = default;
};

template <typename T>
struct in_place_type_t {
    explicit in_place_type_t() = default;
};

template <std::size_t I>
struct in_place_index_t {
    explicit in_place_index_t() = default;
};

#define utility_cpp11_in_place          (utility_cpp11::in_place_t{})
#define utility_cpp11_in_place_type(T)  (utility_cpp11::in_place_type_t<T>{})
#define utility_cpp11_in_place_index(I) (utility_cpp11::in_place_index_t<I>{})

#endif // utility_cpp11_HAS_IN_PLACE

} // namespace utility_cpp11

#if utility_cpp11_CPP11_OR_LATER
namespace bp11 {

using utility_cpp11::exchange;
using utility_cpp11::as_const;
using utility_cpp11::cmp_equal;
using utility_cpp11::cmp_not_equal;
using utility_cpp11::cmp_less;
using utility_cpp11::cmp_greater;
using utility_cpp11::cmp_less_equal;
using utility_cpp11::cmp_greater_equal;
using utility_cpp11::in_range;
using utility_cpp11::integer_sequence;
using utility_cpp11::index_sequence;
using utility_cpp11::make_integer_sequence;
using utility_cpp11::make_index_sequence;
using utility_cpp11::index_sequence_for;
#if utility_cpp11_HAS_INLINE_VARIABLES
using utility_cpp11::in_place;
using utility_cpp11::in_place_type;
using utility_cpp11::in_place_index;
#endif // utility_cpp11_HAS_INLINE_VARIABLES
using utility_cpp11::in_place_t;
using utility_cpp11::in_place_type_t;
using utility_cpp11::in_place_index_t;

#define bp11_in_place          utility_cpp11_in_place
#define bp11_in_place_type(T)  utility_cpp11_in_place_type(T)
#define bp11_in_place_index(I) utility_cpp11_in_place_index(I)

} // namespace bp11
#endif // utility_cpp11_CPP11_OR_LATER

#endif // utility_cpp11_UTILITY_HPP_
