cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(better_engine_control_software
        src/WatchDog.cpp
        src/IntWithinRedline.cpp
        src/ValveRedline.cpp
        src/ECS.cpp
        src/ECS.h
        src/main.cpp
        src/CommandData.cpp)
