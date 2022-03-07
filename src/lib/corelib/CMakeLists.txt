cmake_minimum_required(VERSION 3.20)
project(corelib)

add_library(${PROJECT_NAME} commandlineinput.cpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 17)