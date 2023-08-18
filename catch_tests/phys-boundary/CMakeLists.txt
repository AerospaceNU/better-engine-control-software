# a better description of these tests would probably be "sim-boundary-tests-lib"

add_library(phys-boundary-tests-lib OBJECT
        FakeBoundaryTests.cpp
        SensorDataCalibratorTests.cpp
        PackedStructTests.cpp
        FakeECSValveTests.cpp 
        FakePacketSourceTests.cpp
        )

# linux platforms require us to pass the -latomic flag to the linker to get access to std::atomic

# we have to use target_link_libraries, not target_link_options, which would be more
# readable for sure, but that option doesnt work with static libraries. so even though
# it looks like we're linking to a target named "atomic", what CMake does is change this
# call into a -latomic flag when calling the linker.
target_link_libraries(phys-boundary-tests-lib PRIVATE
        "$<$<PLATFORM_ID:Linux>:atomic>")


target_link_libraries(phys-boundary-tests-lib PRIVATE
        sim-boundary
        sim-valves
        # pi-boundary
        )
