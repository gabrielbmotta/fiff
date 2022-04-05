cmake_minimum_required(VERSION 3.20)
project(FiffFileExplorer)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/${MY_BUILD_NAME}/bin/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/${MY_BUILD_NAME}/lib/)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_options(-Wall -Wextra -Wpedantic -Wabi -Wdouble-promotion -Werror -g)
endif()

if(CMAKE_BUILD_TYPE MATCHES "Release")
    add_compile_options(-Wall -Wextra -Wpedantic -Wabi -Wdouble-promotion -Werror)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)