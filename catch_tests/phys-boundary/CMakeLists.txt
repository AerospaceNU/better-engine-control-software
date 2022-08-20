# a better description of these tests would probably be "sim-boundary-tests-lib"

add_library(phys-boundary-tests-lib OBJECT
        FakeBoundaryTests.cpp
        LinearIntCalibratorTests.cpp
        QuadraticIntCalibratorTests.cpp)

target_link_libraries(phys-boundary-tests-lib PUBLIC
        sim-boundary
        # pi-boundary
        )
