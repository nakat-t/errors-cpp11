#ifndef errors_cpp11_PRIVATE_NONSTD_OPTIONAL_PATCH_HPP_
#define errors_cpp11_PRIVATE_NONSTD_OPTIONAL_PATCH_HPP_

#include <errors_cpp11/private/utility_cpp11/utility.hpp>

#define nonstd_lite_HAVE_IN_PLACE_TYPES  1

namespace nonstd {

using bp11::in_place_t;
using bp11::in_place_type_t;
using bp11::in_place_index_t;

#define nonstd_lite_in_place_t(      T)  bp11::in_place_t
#define nonstd_lite_in_place_type_t( T)  bp11::in_place_type_t<T>
#define nonstd_lite_in_place_index_t(K)  bp11::in_place_index_t<K>

#define nonstd_lite_in_place(      T)    bp11_in_place
#define nonstd_lite_in_place_type( T)    bp11_in_place_type(T)
#define nonstd_lite_in_place_index(K)    bp11_in_place_index(K)

} // namespace nonstd

#include <errors_cpp11/private/nonstd/optional.hpp>

#endif // errors_cpp11_PRIVATE_NONSTD_OPTIONAL_PATCH_HPP_
