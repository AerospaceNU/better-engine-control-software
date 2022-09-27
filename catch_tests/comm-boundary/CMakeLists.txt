add_library(comm-boundary-tests-lib OBJECT
        ParsingHelperTests.cpp
        ECSNetworkerTests.cpp)

target_link_libraries(comm-boundary-tests-lib PUBLIC
        json-comm
        horizontal-ecs
        # logger TODO get logger working again
        sim-boundary
        sequencer
        utils
        constants
        watchdog
        Threads::Threads)