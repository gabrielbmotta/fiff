cmake_minimum_required(VERSION 3.20)
project(test)

include_directories(.)
set(CMAKE_CXX_STANDARD 14)

if(NOT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} STREQUAL "")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/)
    file(INSTALL run_tests DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

add_subdirectory(app)
add_subdirectory(lib)
