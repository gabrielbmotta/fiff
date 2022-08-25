cmake_minimum_required(VERSION 3.0)
project(core)

set(SOURCES
        stringmanip.hpp
        stringmanip.cpp
        endian.hpp
        endian.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)
