cmake_minimum_required(VERSION 3.20)
project(core)

add_library(${PROJECT_NAME} commandlineinput.cpp commandlineinput.hpp
                            stringmanip.cpp stringmanip.hpp
                            endian.cpp endian.hpp
        )

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)
