add_library(json-comm STATIC
        SocketLogger.cpp
        ParsingHelpers.cpp
        IncomingJsonParsers.cpp
        OutgoingJsonParsers.cpp)

target_include_directories(json-comm SYSTEM PUBLIC ../../external)
target_link_libraries(json-comm PUBLIC 
        logger 
        asio) # asio has to be PUBLIC bc included by websocketpp in header file
target_link_libraries(json-comm PRIVATE
        Threads::Threads
        constants)

add_library(fake-comm STATIC
        FakeCommBoundary.cpp)
