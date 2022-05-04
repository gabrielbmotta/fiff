cmake_minimum_required(VERSION 3.20)
project(utils)

set(SOURCES
        commandlineinput.hpp
        commandlineinput.cpp
        )

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)
