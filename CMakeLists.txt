cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(include)

add_subdirectory(catch_tests)
add_subdirectory(src)
