add_subdirectory(redlines)

add_library(watchdog WatchDog.cpp)
target_link_libraries(watchdog PUBLIC redlines)