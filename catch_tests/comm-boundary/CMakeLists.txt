add_library(comm-boundary-tests-lib OBJECT
        ParsingHelperTests.cpp
        SocketLoggerTests.cpp)

target_link_libraries(comm-boundary-tests-lib PUBLIC
        json-comm
        constants
        utils
        sequencer # this is temp
        fake-ecs)