cmake_minimum_required(VERSION 3.20)
project(anonymizer)

add_executable(${PROJECT_NAME}  main.cpp
                                anonymizer.cpp anonymizer.hpp)

target_link_libraries(${PROJECT_NAME}
        core fiff)
