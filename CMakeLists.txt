cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/Wall /EHsc")
ENDIF(MSVC)

include_directories(src)
include_directories(include)

#add_executable(better_engine_control_software
#        src/ECS.cpp
#        src/ECS.h
#        src/logger/Logger.h
#        src/util/consts.h
#        src/util/utils.h
#        src/main.cpp
#        "src/phys-boundary/FakeBoundary.cpp"
#        src/SensorData.cpp
#        src/CommandData.cpp
#        src/logger/Logger.cpp
#        src/util/consts.cpp
#        src/util/utils.cpp
#        src/util/structs.cpp)
#
#add_subdirectory(catch_tests)
#add_subdirectory(src)

add_subdirectory(src)

add_executable(ecs_quick main_tweak.cpp)
target_link_libraries(ecs_quick PUBLIC
        watchdog
        utils-and-constants)

add_executable(ecs_pi main_pi.cpp)
target_link_libraries(ecs_pi PUBLIC
        horizontal_ecs
        logger
        pi_boundary
        sequencer
        utils-and-constants
        watchdog)

add_executable(ecs_sim main_sim.cpp)
target_link_libraries(ecs_sim PUBLIC
        horizontal_ecs
        logger
        sim_boundary
        sequencer
        utils-and-constants
        watchdog)

