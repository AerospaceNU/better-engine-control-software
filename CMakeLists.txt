cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/Wall /EHsc")
ENDIF(MSVC)

include_directories(src)
include_directories(include)

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

add_subdirectory(catch_tests)
add_subdirectory(src)
