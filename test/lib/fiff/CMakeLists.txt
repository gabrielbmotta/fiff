cmake_minimum_required(VERSION 3.20)
project(fiff)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 REQUIRED)

add_executable(${PROJECT_NAME}_test
        main.cpp
        u_input.cpp
        u_output.cpp
        u_tag.cpp
        i_inputoutput.cpp)
target_link_libraries(${PROJECT_NAME}_test PRIVATE Catch2::Catch2 fiff core)
