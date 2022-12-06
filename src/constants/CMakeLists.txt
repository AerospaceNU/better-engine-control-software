add_library(constants
        AllConstants.cpp
        AllCalibrations.cpp
        )

target_link_libraries(constants PUBLIC
        redlines
        sequences
        calibrators
        utils)