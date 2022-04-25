cmake_minimum_required(VERSION 3.20)
project(fiff)

add_library(${PROJECT_NAME}
        tag.cpp tag.hpp
        types.hpp
        input.cpp input.hpp
        output.cpp output.hpp
        formatting.cpp formatting.hpp
        data.cpp data.hpp
        )

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME}
         core)
