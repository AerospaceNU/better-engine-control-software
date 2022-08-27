add_subdirectory(valves)
add_subdirectory(calibrators)

add_library(pi-boundary
        TeensyBoundary.cpp)

# TODO: get the libserial source directly pulled from GitHub
# it builds with CMake as well, so integrating it shouldn't be hard
# it also has updated features (ex. move constructors for LibSerial::SerialPort)

if (IS_CROSS)
    target_link_libraries(pi-boundary PUBLIC libserial_static)
endif()


if (IS_CROSS)
    # Pull in includes for libserial
    find_library(LIBWIRINGPI NAMES wiringPi PATHS ${CMAKE_SOURCE_DIR}/sysroot/usr/lib)
endif()

target_link_libraries(pi-boundary PUBLIC
        pi-valves
        calibrators
        ${LIBWIRINGPI})

add_library(sim-boundary
        FakeBoundary.cpp)
target_link_libraries(sim-boundary PUBLIC
        calibrators)