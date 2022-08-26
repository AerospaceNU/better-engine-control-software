add_library(utils-tests-lib OBJECT
        ThreadSafeQueueTests.cpp
        SensorDataTests.cpp
        CommandDataTests.cpp)

target_link_libraries(utils-tests-lib PUBLIC
        utils
        constants)