add_library(utils-tests-lib OBJECT
        ThreadSafeQueueTests.cpp)

target_link_libraries(utils-tests-lib PUBLIC
        utils-and-constants)