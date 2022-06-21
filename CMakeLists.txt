cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(better_engine_control_software
        src/ECS.cpp
        src/ECS.h
        src/Logger.h
        src/util/consts.h
        src/util/utils.h
        src/main.cpp
        src/FakeBoundary.cpp
        src/SensorData.cpp
        src/CommandData.cpp
        src/Logger.cpp
        src/util/consts.cpp
        src/util/utils.cpp
        src/util/structs.cpp)
