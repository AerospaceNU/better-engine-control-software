#set(FILES_LIST
#        watchdog/WatchDog.cpp
#        watchdog/IntWithinRedline.cpp
#        watchdog/ValveRedline.cpp
#        ecs/HorizontalECS.cpp
#        utils-and-constants/ECSState.cpp
#        sequencer/Sequencer.cpp
#        sequencer/RelatTimedSequence.cpp)
#
#add_subdirectory(utils-and-constants)
#add_library(ecs ${FILES_LIST})
#
#
#target_link_libraries(ecs PUBLIC utils-and-constants)
#
#add_executable(better_engine_control_software ../main.cpp)
#target_link_libraries(better_engine_control_software PRIVATE ecs utils-and-constants)

add_subdirectory(comm-boundary)
add_subdirectory(ecs)
add_subdirectory(logger)
add_subdirectory(phys-boundary)
add_subdirectory(sequencer)
add_subdirectory(utils-and-constants)
add_subdirectory(watchdog)

