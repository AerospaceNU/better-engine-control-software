add_library(constants
        AllConstants.cpp
        HorizontalCalibrations.cpp
        )

target_link_libraries(constants PUBLIC
        redlines
        sequences
        utils)