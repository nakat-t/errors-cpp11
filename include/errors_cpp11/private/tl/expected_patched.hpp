#ifndef errors_cpp11_PRIVATE_TL_EXPECTED_PATCH_HPP_
#define errors_cpp11_PRIVATE_TL_EXPECTED_PATCH_HPP_

#include <errors_cpp11/private/utility_cpp11/utility.hpp>

namespace tl {
class monostate {};
using bp11::in_place_t;
}

#define TL_MONOSTATE_INPLACE_MUTEX
#define in_place bp11_in_place
#include <errors_cpp11/private/tl/expected.hpp>
#undef in_place

#endif // errors_cpp11_PRIVATE_TL_EXPECTED_PATCH_HPP_
