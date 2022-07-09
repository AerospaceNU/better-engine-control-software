add_subdirectory(valves)
add_library(pi-boundary
        TeensyBoundary.cpp)
target_link_libraries(pi-boundary PUBLIC pi-valves)

add_library(sim-boundary
        FakeBoundary.cpp)