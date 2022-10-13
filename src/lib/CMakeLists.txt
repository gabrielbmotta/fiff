cmake_minimum_required(VERSION 3.0)
project(lib)

if(NOT ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} STREQUAL "")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libs/)
endif()

if(NOT ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} STREQUAL "")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/libs/)
endif()

add_subdirectory(core)
add_subdirectory(fiff)
add_subdirectory(utils)

if(DEFINED QT_APPS)
    add_subdirectory(qtui)
endif()
