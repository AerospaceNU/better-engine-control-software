add_library(ecs-tests-lib OBJECT
        StandECSTests.cpp)

target_link_libraries(ecs-tests-lib PRIVATE
        stand-ecs
        fake-comm
        sim-boundary
        fake-watchdog
        sequencer
        fake-sequences
        utils
        )
