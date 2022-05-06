cmake_minimum_required(VERSION 3.20)
project(src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/bin/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/lib/)

add_compile_options(-Wall -Wextra -Wpedantic -Wdouble-promotion -Werror)

if(NOT (CMAKE_CXX_STANDARD EQUAL 98))
    add_subdirectory(app)
endif()

add_subdirectory(lib)
