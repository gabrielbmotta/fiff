cmake_minimum_required(VERSION 3.20)
project(src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/bin/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/lib/)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-Wall -Wextra -Wpedantic -Wdouble-promotion -Werror -g -O0 -ftest-coverage -fprofile-arcs)
    add_link_options(--coverage)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_compile_options(-Wall -Wextra -Wpedantic -Wdouble-promotion -Werror)
endif()

add_subdirectory(app)
add_subdirectory(lib)
