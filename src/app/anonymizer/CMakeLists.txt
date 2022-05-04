cmake_minimum_required(VERSION 3.20)
project(anonymizer)

set(SOURCES
        anonymizer.hpp
        anonymizer.cpp
        main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        core fiff utils)
