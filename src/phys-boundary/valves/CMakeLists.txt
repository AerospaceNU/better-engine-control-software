add_library(pi-valves
        ECSPiValve.cpp
        ECSThreeWayPiValve.cpp)

target_link_libraries(pi-valves
        wiringPi)