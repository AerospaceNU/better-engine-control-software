add_subdirectory(valves)
add_subdirectory(calibrators)
add_subdirectory(packet-sources)

add_library(pi-boundary STATIC
        TeensyBoundary.cpp)

target_link_libraries(pi-boundary PUBLIC
        pi-valves
        calibrators
        serial-packets
        )


add_library(sim-boundary STATIC
        FakeBoundary.cpp)
# we dont actually calibrate on the fake boundary, since its just random data
# target_link_libraries(sim-boundary PUBLIC
#         calibrators)
