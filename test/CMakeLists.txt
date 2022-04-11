cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2)
if(Catch2_FOUND)
    add_subdirectory(app)
    add_subdirectory(lib)
endif()



