add_library(constants
        HorizontalECSStates.cpp
        HorizontalCalibrations.cpp
        )
target_link_libraries(constants PUBLIC
        redlines
        utils)