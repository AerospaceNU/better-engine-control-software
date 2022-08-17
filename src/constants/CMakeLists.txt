add_library(constants
        HorizontalECSStates.cpp)
target_link_libraries(constants PUBLIC
        redlines
        utils)