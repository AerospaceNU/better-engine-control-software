add_library(comm-boundary-tests-lib OBJECT
        ParsingHelperTests.cpp
        SocketLoggerTests.cpp
        OutgoingJsonParsersTests.cpp IncomingJsonParsersTests.cpp)

target_link_libraries(comm-boundary-tests-lib PRIVATE
        json-comm
        constants
        utils
        sequencer # this is temp
        fake-ecs)
