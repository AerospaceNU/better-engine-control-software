add_library(json-comm STATIC
        SocketLogger.cpp
        ParsingHelpers.cpp
        IncomingJsonParsers.cpp
        OutgoingJsonParsers.cpp GlobalCommBoundary.h GlobalCommBoundary.cpp)


target_include_directories(json-comm SYSTEM PUBLIC ../../external)
target_link_libraries(json-comm PUBLIC logger)
target_link_libraries(json-comm PRIVATE
        Threads::Threads
        constants)

add_library(fake-comm STATIC
        FakeCommBoundary.cpp)
