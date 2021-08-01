// Copyright (c) 2021 nakat-t <armaiti.wizard@gmail.com>
// This code is licensed under MIT license. see LICENSE file.

#ifndef errors_cpp11_VERSION_HPP_
#define errors_cpp11_VERSION_HPP_

#define errors_cpp11_VERSION_MAJOR 0
#define errors_cpp11_VERSION_MINOR 1
#define errors_cpp11_VERSION_PATCH 0

#define errors_cpp11_STR(v) #v
#define errors_cpp11_VERSION_(major, minor, patch) errors_cpp11_STR(major) "." errors_cpp11_STR(minor) "." errors_cpp11_STR(patch)
#define errors_cpp11_VERSION errors_cpp11_VERSION_(errors_cpp11_VERSION_MAJOR, errors_cpp11_VERSION_MINOR, errors_cpp11_VERSION_PATCH)

#endif // errors_cpp11_VERSION_HPP_
