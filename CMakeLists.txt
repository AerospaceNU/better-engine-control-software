cmake_minimum_required(VERSION 3.16)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 17)
# set (CMAKE_CXX_STANDARD_REQUIRED ON)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/Wall /EHsc /Os /Oy /Ob0 /GF /Gy")
    # STRING(REPLACE "/Od" "/O1" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
ENDIF(MSVC)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# this makes it so we can reference header files from the src/ folder, instead of a relative path
include_directories(src)

add_subdirectory(catch_tests)
add_subdirectory(src)
add_subdirectory(external)

add_executable(ecs_quick main_tweak.cpp)
target_link_libraries(ecs_quick PUBLIC
        watchdog
        constants)


add_executable(ecs_pi main_pi.cpp)

if (IS_CROSS)
        target_include_directories(ecs_pi PUBLIC sysroot/usr/include)
        find_library(LIBSERIAL NAMES serial PATHS ${CMAKE_SOURCE_DIR}/sysroot/usr/lib)
        find_library(LIBWIRINGPI NAMES wiringPi PATHS ${CMAKE_SOURCE_DIR}/sysroot/usr/lib)
else()
        find_package(PkgConfig)
        pkg_check_modules(SERIAL libserial)
endif()

target_link_libraries(ecs_pi PUBLIC
        json-comm
        horizontal-ecs
        # logger TODO get logger working again
        pi-boundary
        sequencer
        utils
        constants
        watchdog
        Threads::Threads
        # wtf are these i copied pasted it from the old ecs
        ${SERIAL_LDFLAGS} ${CMAKE_THREAD_LIBS_INIT} ${LIBWIRINGPI})

add_executable(ecs_sim main_sim.cpp)
target_link_libraries(ecs_sim PUBLIC
        json-comm
        horizontal-ecs
        # logger TODO get logger working again
        sim-boundary
        sequencer
        utils
        constants
        watchdog
        Threads::Threads)

# just tinkering
# target_link_options(ecs_sim PRIVATE "/MAP:${PROJECT_SOURCE_DIR}/cmake-build-debug/ecs_sim.map")
