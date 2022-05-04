cmake_minimum_required(VERSION 3.20)
project(fiffsplice)

set(SOURCES
        main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        core fiff utils)
