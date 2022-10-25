add_library(watchdog-tests-lib OBJECT
        IntWithinRedlineTests.cpp ValveWithinRedlineTests.cpp)

target_link_libraries(watchdog-tests-lib PUBLIC
        watchdog)