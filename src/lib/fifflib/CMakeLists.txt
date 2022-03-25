cmake_minimum_required(VERSION 3.20)
project(fifflib)

add_library(${PROJECT_NAME} tag.cpp include/fiff/tag.hpp
                            filein.cpp include/fiff/filein.hpp
                            fileout.cpp include/fiff/fileout.hpp
                            idmap.cpp include/fiff/idmap.hpp)

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
         corelib)

set(CMAKE_CXX_STANDARD 17)