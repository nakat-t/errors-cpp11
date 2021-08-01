// Copyright (c) 2016 Martin Moene
//
// https://github.com/martinmoene/optional-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef TEST_OPTIONAL_LITE_H_INCLUDED
#define TEST_OPTIONAL_LITE_H_INCLUDED

#include <errors_cpp11/errors.hpp>

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include "lest_cpp03.hpp"

#undef EXPECT
#define EXPECT REQUIRE

#undef EXPECT_NOT
#define EXPECT_NOT REQUIRE_FALSE

#undef EXPECT_THROWS_AS
#define EXPECT_THROWS_AS REQUIRE_THROWS_AS

#undef SETUP
#define SETUP(...)

#undef SECTION

#define CASE( name ) TEST_CASE( name )


#include <catch2/catch.hpp>

#endif // TEST_OPTIONAL_LITE_H_INCLUDED

// end of file
