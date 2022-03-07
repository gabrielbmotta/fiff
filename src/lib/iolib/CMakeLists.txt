cmake_minimum_required(VERSION 3.20)
project(iolib)

add_library(${PROJECT_NAME} include/io/endian.hpp
                            file.cpp include/io/file.hpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)