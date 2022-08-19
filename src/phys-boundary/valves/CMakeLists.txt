add_library(pi-valves
    ECSPiValve.cpp
    ECSThreeWayPiValve.cpp)

if (IS_CROSS)
    # Pull in includes for libserial
    target_include_directories(pi-valves PUBLIC ${CMAKE_SOURCE_DIR}/sysroot/usr/include)
    find_library(LIBWIRINGPI NAMES wiringPi PATHS ${CMAKE_SOURCE_DIR}/sysroot/usr/lib)
endif()

target_link_libraries(pi-valves
        ${LIBWIRINGPI})