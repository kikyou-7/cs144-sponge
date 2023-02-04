cmake_minimum_required (VERSION 2.8.5)
cmake_policy (SET CMP0054 NEW)
project (Sponge)


# set (CMAKE_C_COMPILER "/usr/bin/clang-12")
# set (CMAKE_CXX_COMPILER "/usr/bin/clang++-12")
# 用gcc作为编译器
add_compile_options(-std=c++17 -Wall -Werror)
include (etc/build_defs.cmake)
include (etc/build_type.cmake)
include (etc/cflags.cmake)

include (etc/doxygen.cmake)

include (etc/clang_format.cmake)
include (etc/clang_tidy.cmake)
include (etc/cppcheck.cmake)

include_directories ("${PROJECT_SOURCE_DIR}/libsponge/util")
include_directories ("${PROJECT_SOURCE_DIR}/libsponge/tcp_helpers")
include_directories ("${PROJECT_SOURCE_DIR}/libsponge")

add_subdirectory ("${PROJECT_SOURCE_DIR}/libsponge")

add_subdirectory ("${PROJECT_SOURCE_DIR}/apps")

add_subdirectory ("${PROJECT_SOURCE_DIR}/tests")

add_subdirectory ("${PROJECT_SOURCE_DIR}/doctests")

include (etc/tests.cmake)
