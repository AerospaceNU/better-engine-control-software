add_subdirectory(valves)
add_subdirectory(calibrators)

add_library(pi-boundary
        TeensyBoundary.cpp)
target_link_libraries(pi-boundary PUBLIC
        pi-valves
        calibrators
        wiringPi)

add_library(sim-boundary
        FakeBoundary.cpp)
target_link_libraries(sim-boundary PUBLIC
        calibrators)