if(build_cmake_test_cmake_included)
  return()
endif()
set(build_cmake_test_cmake_included true)

include(build/cmake/test.lists.cmake)

add_executable(
    test_errors_cpp11
    EXCLUDE_FROM_ALL
    ${test_sources}
)

target_include_directories(
    test_errors_cpp11
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/externals/catchorg/Catch2/single_include"
    "${PROJECT_SOURCE_DIR}/test"
)

add_custom_target(test DEPENDS test_errors_cpp11)
