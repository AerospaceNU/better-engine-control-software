add_library(watchdog-tests-lib OBJECT
        IntWithinRedlineTests.cpp
        ValveWithinRedlineTests.cpp
        FakeWatchDogTests.cpp
        FakeRedlineTests.cpp)

target_link_libraries(watchdog-tests-lib PRIVATE
        redlines
        fake-watchdog)
