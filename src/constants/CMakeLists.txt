add_library(constants STATIC
        AllConstants.cpp
        AllCalibrations.cpp
        )

target_link_libraries(constants PRIVATE
        redlines
        sequences
        calibrators
        utils)
