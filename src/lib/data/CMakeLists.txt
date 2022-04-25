cmake_minimum_required(VERSION 3.20)
project(data)

set(SOURCES
        parse.hpp
        parse.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME}
        fiff core)
