cmake_minimum_required(VERSION 3.20)
project(fifflib)

add_library(${PROJECT_NAME} )

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
        fifflib)

set(CMAKE_CXX_STANDARD 17)