cmake_minimum_required(VERSION 3.13)

project(errors_cpp11 VERSION 0.0.1 LANGUAGES CXX)

#--------------------------------------------------------------------
# プロジェクト基本設定
#--------------------------------------------------------------------

# Debug/Release
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# C++ 標準 = C++11 必須, コンパイラ拡張無効
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------------------------------------------------------------
# MSVC 固有設定
#--------------------------------------------------------------------

if(MSVC)
    add_compile_definitions(
        _CRT_SECURE_NO_WARNINGS
        _SCL_SECURE_NO_WARNINGS
        NOMINMAX
    )
    add_compile_options(
        "/utf-8"
    )
    # >= Visual Studio 2017
    if(${MSVC_TOOLSET_VERSION} GREATER_EQUAL 141)
        add_compile_options(
            "/Zc:__cplusplus"
        )
    endif()
endif()

#--------------------------------------------------------------------
# 生成ターゲットごとの cmake ファイルインクルード
#--------------------------------------------------------------------

include(build/cmake/test.cmake)
