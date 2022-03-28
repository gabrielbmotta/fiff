cmake_minimum_required(VERSION 3.20)
project(fifflib)

add_library(${PROJECT_NAME} tag.cpp include/fiff/tag.hpp
        input.cpp include/fiff/input.hpp
        output.cpp include/fiff/output.hpp
        formatting.cpp include/fiff/formatting.hpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
         corelib)

set(CMAKE_CXX_STANDARD 17)