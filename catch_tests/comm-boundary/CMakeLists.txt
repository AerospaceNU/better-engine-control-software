add_library(comm-boundary-tests-lib OBJECT
        ParsingHelperTests.cpp)

target_link_libraries(comm-boundary-tests-lib PUBLIC
        json-comm
        constants)