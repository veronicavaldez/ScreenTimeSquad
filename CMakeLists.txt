# cmake_minimum_required(VERSION <specify CMake version here>)
project(ScreenTimeSquad)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ScreenTimeSquad
        src/algorithms.cpp
        src/algorithms.h
        src/data_parser.cpp
        src/data_parser.h
        src/main.cpp)
