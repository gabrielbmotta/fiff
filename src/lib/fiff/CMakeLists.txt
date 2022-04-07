cmake_minimum_required(VERSION 3.20)
project(fiff)

add_library(${PROJECT_NAME}
        include/fiff/tag.hpp
        include/fiff/types.hpp
        input.cpp include/fiff/input.hpp
        output.cpp include/fiff/output.hpp
        formatting.cpp include/fiff/formatting.hpp
        data.cpp include/fiff/data.hpp
        )

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
         core)

set(CMAKE_CXX_STANDARD 17)