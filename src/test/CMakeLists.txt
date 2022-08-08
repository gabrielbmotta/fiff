cmake_minimum_required(VERSION 3.20)
project(test)

include_directories(.)
set(CMAKE_CXX_STANDARD 14)
set(RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY}/test)

file(INSTALL run_tests DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
add_subdirectory(app)
add_subdirectory(lib)
