// Copyright (c) 2021 nakat-t <armaiti.wizard@gmail.com>
// This code is licensed under MIT license. see LICENSE file.

#ifndef errors_cpp11_TRY_HPP_
#define errors_cpp11_TRY_HPP_

#include <errors_cpp11/expected.hpp>
#include <errors_cpp11/optional.hpp>

namespace errors {

template <typename T, typename E>
inline
bool
try_operation_has_value(const errors::expected<T, E>& e)
{
    return e.has_value();
}

template <typename T>
inline
bool
try_operation_has_value(const errors::optional<T>& o)
{
    return o.has_value();
}

template <typename T, typename E>
inline
T&&
try_operation_extract_value(errors::expected<T, E>&& e)
{
    return std::forward<T>(e.value());
}

template <typename T>
inline
T&&
try_operation_extract_value(errors::optional<T>&& o)
{
    return std::forward<T>(o.value());
}

template <typename T, typename E>
inline
errors::unexpected<E>
try_operation_return_as(const errors::expected<T, E>& e)
{
    return errors::make_unexpected(e.error());
}

template <typename T>
inline
nullopt_t
try_operation_return_as(const errors::optional<T>& o)
{
    return errors::nullopt;
}

} // namespace errors

#define errors_cpp11_TRY_GLUE2(x, y) x##y
#define errors_cpp11_TRY_GLUE(x, y) errors_cpp11_TRY_GLUE2(x, y)
#define errors_cpp11_TRY_UNIQUE_NAME errors_cpp11_TRY_GLUE(_outcome_try_unique_name_temporary, __COUNTER__)
#define errors_cpp11_TRY_RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, count, ...) count
#define errors_cpp11_TRY_EXPAND_ARGS(args) errors_cpp11_TRY_RETURN_ARG_COUNT args
#define errors_cpp11_TRY_COUNT_ARGS_MAX8(...) errors_cpp11_TRY_EXPAND_ARGS((__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define errors_cpp11_TRY_OVERLOAD_MACRO2(name, count) name##count
#define errors_cpp11_TRY_OVERLOAD_MACRO1(name, count) errors_cpp11_TRY_OVERLOAD_MACRO2(name, count)
#define errors_cpp11_TRY_OVERLOAD_MACRO(name, count) errors_cpp11_TRY_OVERLOAD_MACRO1(name, count)
#define errors_cpp11_TRY_OVERLOAD_GLUE(x, y) x y
#define errors_cpp11_TRY_CALL_OVERLOAD(name, ...) errors_cpp11_TRY_OVERLOAD_GLUE(errors_cpp11_TRY_OVERLOAD_MACRO(name, errors_cpp11_TRY_COUNT_ARGS_MAX8(__VA_ARGS__)), (__VA_ARGS__))
#define _errors_cpp11_TRY_RETURN_ARG_COUNT(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, count, ...) count
#define _errors_cpp11_TRY_EXPAND_ARGS(args) _errors_cpp11_TRY_RETURN_ARG_COUNT args
#define _errors_cpp11_TRY_COUNT_ARGS_MAX8(...) _errors_cpp11_TRY_EXPAND_ARGS((__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define _errors_cpp11_TRY_OVERLOAD_MACRO2(name, count) name##count
#define _errors_cpp11_TRY_OVERLOAD_MACRO1(name, count) _errors_cpp11_TRY_OVERLOAD_MACRO2(name, count)
#define _errors_cpp11_TRY_OVERLOAD_MACRO(name, count) _errors_cpp11_TRY_OVERLOAD_MACRO1(name, count)
#define _errors_cpp11_TRY_OVERLOAD_GLUE(x, y) x y
#define _errors_cpp11_TRY_CALL_OVERLOAD(name, ...) _errors_cpp11_TRY_OVERLOAD_GLUE(_errors_cpp11_TRY_OVERLOAD_MACRO(name, _errors_cpp11_TRY_COUNT_ARGS_MAX8(__VA_ARGS__)), (__VA_ARGS__))
#ifndef errors_cpp11_TRY_LIKELY_IF
#if (__cplusplus >= 202000L) && (!defined(__clang__) || __clang_major__ >= 12)
#define errors_cpp11_TRY_LIKELY_IF(...) if(__VA_ARGS__) [[likely]]
#elif defined(__clang__) || defined(__GNUC__)
#define errors_cpp11_TRY_LIKELY_IF(...) if(__builtin_expect(!!(__VA_ARGS__), true))
#else
#define errors_cpp11_TRY_LIKELY_IF(...) if(__VA_ARGS__)
#endif
#endif
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_UNPACK(...) __VA_ARGS__
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE3(unique, ...) auto unique = (__VA_ARGS__)
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE2(x) x
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE(unique, x, ...) errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE2(errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE3(unique, __VA_ARGS__))
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED3(unique, x, y, ...) x unique = (__VA_ARGS__)
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED2(x) x
#define errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED(unique, ...) errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED2(errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED3(unique, __VA_ARGS__))
#define errors_cpp11_TRYV2_UNIQUE_STORAGE1(...) errors_cpp11_TRYV2_UNIQUE_STORAGE_DEDUCE
#define errors_cpp11_TRYV2_UNIQUE_STORAGE2(...) errors_cpp11_TRYV2_UNIQUE_STORAGE_SPECIFIED
#define errors_cpp11_TRYV2_UNIQUE_STORAGE(unique, spec, ...) _errors_cpp11_TRY_CALL_OVERLOAD(errors_cpp11_TRYV2_UNIQUE_STORAGE, errors_cpp11_TRYV2_UNIQUE_STORAGE_UNPACK spec) (unique, errors_cpp11_TRYV2_UNIQUE_STORAGE_UNPACK spec, __VA_ARGS__)
#define errors_cpp11_TRYV2_SUCCESS_LIKELY(unique, retstmt, spec, ...) errors_cpp11_TRYV2_UNIQUE_STORAGE(unique, spec, __VA_ARGS__); errors_cpp11_TRY_LIKELY_IF(::errors::try_operation_has_value(unique)); else retstmt ::errors::try_operation_return_as(static_cast<decltype(unique) &&>(unique))
#define errors_cpp11_TRY2_VAR_SECOND2(x, var) var
#define errors_cpp11_TRY2_VAR_SECOND3(x, y, ...) x y
#define errors_cpp11_TRY2_VAR(spec) _errors_cpp11_TRY_CALL_OVERLOAD(errors_cpp11_TRY2_VAR_SECOND, errors_cpp11_TRYV2_UNIQUE_STORAGE_UNPACK spec, spec)
#define errors_cpp11_TRY2_SUCCESS_LIKELY(unique, retstmt, var, ...) errors_cpp11_TRYV2_SUCCESS_LIKELY(unique, retstmt, var, __VA_ARGS__); errors_cpp11_TRY2_VAR(var) = ::errors::try_operation_extract_value(static_cast<decltype(unique) &&>(unique))
#define errors_cpp11_TRYV(...) errors_cpp11_TRYV2_SUCCESS_LIKELY(errors_cpp11_TRY_UNIQUE_NAME, return, deduce, __VA_ARGS__)
#define errors_cpp11_TRYA(v, ...) errors_cpp11_TRY2_SUCCESS_LIKELY(errors_cpp11_TRY_UNIQUE_NAME, return, v, __VA_ARGS__)
#define errors_cpp11_TRY_INVOKE_TRY8(a, b, c, d, e, f, g, h) errors_cpp11_TRYA(a, b, c, d, e, f, g, h)
#define errors_cpp11_TRY_INVOKE_TRY7(a, b, c, d, e, f, g) errors_cpp11_TRYA(a, b, c, d, e, f, g)
#define errors_cpp11_TRY_INVOKE_TRY6(a, b, c, d, e, f) errors_cpp11_TRYA(a, b, c, d, e, f)
#define errors_cpp11_TRY_INVOKE_TRY5(a, b, c, d, e) errors_cpp11_TRYA(a, b, c, d, e)
#define errors_cpp11_TRY_INVOKE_TRY4(a, b, c, d) errors_cpp11_TRYA(a, b, c, d)
#define errors_cpp11_TRY_INVOKE_TRY3(a, b, c) errors_cpp11_TRYA(a, b, c)
#define errors_cpp11_TRY_INVOKE_TRY2(a, b) errors_cpp11_TRYA(a, b)
#define errors_cpp11_TRY_INVOKE_TRY1(a) errors_cpp11_TRYV(a)

#define ERRORS_TRY(...) errors_cpp11_TRY_CALL_OVERLOAD(errors_cpp11_TRY_INVOKE_TRY, __VA_ARGS__)

#endif // errors_cpp11_TRY_HPP_
