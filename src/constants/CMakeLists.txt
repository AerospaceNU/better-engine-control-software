add_library(constants
        HorizontalECSStates.cpp
        HorizontalCalibrations.cpp
        Strings.cpp)
target_link_libraries(constants PUBLIC
        redlines
        utils)