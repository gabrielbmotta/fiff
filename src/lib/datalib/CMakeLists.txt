cmake_minimum_required(VERSION 3.20)
project(datalib)

add_library(${PROJECT_NAME} parse.cpp   include/data/parse.hpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
        fifflib corelib)

set(CMAKE_CXX_STANDARD 17)