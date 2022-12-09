add_subdirectory(redlines)

add_library(fake-watchdog FakeWatchDog.cpp)
target_link_libraries(fake-watchdog PUBLIC redlines)