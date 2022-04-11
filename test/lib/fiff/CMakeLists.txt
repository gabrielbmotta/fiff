cmake_minimum_required(VERSION 3.20)
project(fiff)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 REQUIRED)

add_executable(test_${PROJECT_NAME} test.cpp)
target_link_libraries(test_${PROJECT_NAME} PRIVATE Catch2::Catch2)
