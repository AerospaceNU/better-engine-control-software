cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(include)

add_executable(better_engine_control_software
        src/main.cpp
        src/WatchDog.cpp
        src/IntWithinRedline.cpp
        src/ValveRedline.cpp
        src/IECS.cpp
        src/HorizontalECS.cpp
        src/utils-and-constants/ECSUtils.cpp
        src/utils-and-constants/HorizontalECSRedlines.cpp
        src/Sequencer.cpp
        src/RelatTimedSequence.cpp
        )
