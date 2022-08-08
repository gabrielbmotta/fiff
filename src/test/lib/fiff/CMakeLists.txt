cmake_minimum_required(VERSION 3.20)
project(fiff_test)

set(SOURCES
        main.cpp
        u_input.cpp
        u_output.cpp
        u_tag.cpp
        u_data.cpp
        i_inputoutput.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE fiff core)
