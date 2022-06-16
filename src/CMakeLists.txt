set(FILES_LIST
        WatchDog.cpp
        IntWithinRedline.cpp
        ValveRedline.cpp
        IECS.cpp
        HorizontalECS.cpp
        utils-and-constants/ECSUtils.cpp
        utils-and-constants/HorizontalECSRedlines.cpp
        Sequencer.cpp
        RelatTimedSequence.cpp)

add_subdirectory(utils-and-constants)
add_library(ecs ${FILES_LIST})


add_executable(better_engine_control_software main.cpp)
target_link_libraries(better_engine_control_software PRIVATE ecs utils-and-constants)