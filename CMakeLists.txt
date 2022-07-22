cmake_minimum_required(VERSION 3.21)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)
# set (CMAKE_CXX_STANDARD_REQUIRED ON)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/Wall /EHsc /Os /Oy /Ob0 /GF /Gy")
    # STRING(REPLACE "/Od" "/O1" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
ENDIF(MSVC)

find_package(Threads REQUIRED)

# this makes it so we can reference header files from the src/ folder, instead of a relative path
include_directories(src)
#add_executable(better_engine_control_software
#        src/ECS.cpp
#        src/ECS.h
#        src/logger/Logger.h
#        src/util/consts.h
#        src/util/utils.h
#        src/main.cpp
#        "src/phys-CommBoundary/FakeBoundary.cpp"
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
add_subdirectory(external)

add_executable(ecs_quick main_tweak.cpp)
target_link_libraries(ecs_quick PUBLIC
        watchdog
        utils-and-constants)


find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)

add_executable(ecs_pi main_pi.cpp)
target_link_libraries(ecs_pi PUBLIC
        json-comm
        horizontal-ecs
        # logger
        pi-boundary
        sequencer
        utils-and-constants
        watchdog
        Threads::Threads
        wiringPi
        # wtf are these i copied pasted it from the old ecs
        ${SERIAL_LDFLAGS} ${CMAKE_THREAD_LIBS_INIT})

add_executable(ecs_sim main_sim.cpp)
target_link_libraries(ecs_sim PUBLIC
        json-comm
        horizontal-ecs
        # logger
        sim-boundary
        sequencer
        utils-and-constants
        watchdog)

