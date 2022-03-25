cmake_minimum_required(VERSION 3.20)
project(corelib)

add_library(${PROJECT_NAME} commandlineinput.cpp include/core/commandlineinput.hpp
                            stringmanip.cpp include/core/stringmanip.hpp
                            endian.cpp include/core/endian.hpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)