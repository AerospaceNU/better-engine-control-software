add_subdirectory(valves)
add_subdirectory(calibrators)

add_library(pi-boundary
        TeensyBoundary.cpp)
target_link_libraries(pi-boundary PUBLIC pi-valves calibrators)

add_library(sim-boundary
        FakeBoundary.cpp)