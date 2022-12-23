add_library(json-comm
        SocketLogger.cpp
        ParsingHelpers.cpp
        IncomingJsonParsers.cpp
        OutgoingJsonParsers.cpp)


target_include_directories(json-comm SYSTEM PUBLIC ../../external)
target_link_libraries(json-comm PUBLIC logger)
target_link_libraries(json-comm PRIVATE
        Threads::Threads
        constants)

add_library(fake-comm
        FakeCommBoundary.cpp)