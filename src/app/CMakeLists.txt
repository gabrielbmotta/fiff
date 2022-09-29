cmake_minimum_required(VERSION 3.0)
project(app)

if(NOT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} STREQUAL "")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/apps/)
endif()

add_subdirectory(printfiff)
add_subdirectory(qtprintfiff)
add_subdirectory(qfiff)
add_subdirectory(anonymizer)
add_subdirectory(fiffsplice)
add_subdirectory(fiffdoctor)

