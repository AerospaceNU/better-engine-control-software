add_subdirectory(redlines)

add_library(fake-watchdog STATIC 
    FakeWatchDog.cpp)
add_library(average-watchdog STATIC
    AverageWatchDog.cpp)
target_link_libraries(fake-watchdog PUBLIC 
    redlines)
target_link_libraries(average-watchdog PUBLIC 
    redlines)