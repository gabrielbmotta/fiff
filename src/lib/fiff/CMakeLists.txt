cmake_minimum_required(VERSION 3.20)
project(fiff)

set(SOURCES
        types.hpp
        tag.hpp
        tag.cpp
        input.hpp
        input.cpp
        output.hpp
        output.cpp
        formatting.hpp
        formatting.cpp
        data.hpp
        data.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME}
         core)
