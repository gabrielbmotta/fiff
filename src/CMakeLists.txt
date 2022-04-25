cmake_minimum_required(VERSION 3.20)
project(src)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/bin/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/${MY_BUILD_NAME}/lib/)

add_subdirectory(app)
add_subdirectory(lib)
