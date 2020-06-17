cmake_minimum_required(VERSION 3.15)

set(BISON_EXECUTABLE /usr/local/Cellar/bison/3.2.2/bin/bison)

project(compiler VERSION 1.0
    DESCRIPTION "Very nice project"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(Headers ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(lib)
add_subdirectory(extern)
add_subdirectory(tests)