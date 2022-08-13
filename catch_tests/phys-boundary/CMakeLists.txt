add_library(phys-boundary-tests-lib OBJECT
        FakeBoundaryTests.cpp)

target_link_libraries(phys-boundary-tests-lib PUBLIC
        sim-boundary
        # pi-boundary
        )
