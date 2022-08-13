add_subdirectory(phys-boundary)

add_executable(phys_boundary_tests
        catch_runner.cpp)
target_link_libraries(phys_boundary_tests PUBLIC
        phys-boundary-tests-lib)
