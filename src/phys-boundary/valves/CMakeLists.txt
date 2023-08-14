add_library(pi-valves STATIC
        ECSPiValve.cpp
        ECSThreeWayPiValve.cpp)
target_link_libraries(pi-valves PRIVATE
        wiringPi)

add_library(sim-valves STATIC
        FakeECSValve.cpp)
