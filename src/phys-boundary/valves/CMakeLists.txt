add_library(pi-valves
        ECSPiValve.cpp
        ECSThreeWayPiValve.cpp)

target_include_directories(pi-valves PUBLIC ../../../external/wiringPi/include)

# TODO: we should probably move this into the wiringPi folder
if (IS_CROSS)
#    target_include_directories(pi-valves PUBLIC "../../../external/wiringPi/include")
#    target_link_directories(pi-valves PUBLIC "../../../external/wiringPi/lib")
#    target_link_libraries(pi-valves PUBLIC libwiringPi libwiringPiDev)

    # Pull in lib files for wiringPi
    find_library(WIRINGPI_LIB
            NAMES wiringPi
            PATHS ../../../external/wiringPi/lib
            )

    target_link_libraries(pi-valves PRIVATE
            ${WIRINGPI_LIB})
endif()