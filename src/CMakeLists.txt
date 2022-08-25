cmake_minimum_required(VERSION 3.0)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Wpedantic -Wdouble-promotion -Werror)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-g -O0 -ftest-coverage -fprofile-arcs)
    add_link_options(--coverage)
    add_subdirectory(test)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib)

if(NOT (CMAKE_CXX_STANDARD EQUAL 98))
    add_subdirectory(app)
endif()