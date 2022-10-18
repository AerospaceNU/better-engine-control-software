add_library(json-comm ECSNetworker.cpp ParsingHelpers.cpp)

target_include_directories(json-comm SYSTEM PUBLIC ../../external)
target_link_libraries(json-comm PRIVATE
        Threads::Threads
        constants)