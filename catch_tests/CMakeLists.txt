
# building tests for physical boundary
add_subdirectory(phys-boundary)
add_executable(phys_boundary_tests
        catch_runner.cpp)
target_link_libraries(phys_boundary_tests PUBLIC
        phys-boundary-tests-lib)

# building tests for sequencer
add_subdirectory(sequencer)
add_executable(sequencer_tests
        catch_runner.cpp)
target_link_libraries(sequencer_tests PUBLIC
        sequencer-tests-lib)