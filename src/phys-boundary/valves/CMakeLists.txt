if (IS_CROSS)
    add_library(pi-valves
            ECSPiValve.cpp
            ECSThreeWayPiValve.cpp)

#    target_include_directories(pi-valves PUBLIC "../../../external/wiringPi/include")
#    target_link_directories(pi-valves PUBLIC "../../../external/wiringPi/lib")
#    target_link_libraries(pi-valves PUBLIC libwiringPi libwiringPiDev)

    # Pull in includes and lib files for wiringPi
    target_include_directories(pi-valves PUBLIC ../../../external/wiringPi/include)
    find_library(LIBWIRINGPI_LIB
            NAMES wiringPi
            PATHS ../../../external/wiringPi/lib
            )

    target_link_libraries(pi-valves PRIVATE
            ${LIBWIRINGPI})
endif()