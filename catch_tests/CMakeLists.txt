set(TESTS_LIST
        WatchDogTests.cpp
        RelatTimedSequenceTests.cpp catch_runner.cpp)

add_executable(Catch_tests ${TESTS_LIST})
target_link_libraries(Catch_tests ecs)