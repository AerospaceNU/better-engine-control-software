add_subdirectory(valves)
add_library(pi_boundary
        TeensyBoundary.cpp)
target_link_libraries(pi_boundary PUBLIC pi_valves)

add_library(sim_boundary
        FakeBoundary.cpp)