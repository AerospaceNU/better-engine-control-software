add_compile_options("${WARNINGS_LIST}")

# currently we have a mini convention that executables use underscores (ex. exe_name)
# while libraries use hyphens (ex. lib-name)
# we can probably change this later if it's unhelpful/straight up harmful

# building tests for comm boundary
add_subdirectory(comm-boundary)
add_executable(comm_boundary_tests
        catch_runner.cpp)
target_link_libraries(comm_boundary_tests PRIVATE
        comm-boundary-tests-lib)

# building tests for physical boundary
add_subdirectory(phys-boundary)
add_executable(phys_boundary_tests
        catch_runner.cpp)
target_link_libraries(phys_boundary_tests PRIVATE
        phys-boundary-tests-lib)


# building tests for sequencer
add_subdirectory(sequencer)
add_executable(sequencer_tests
        catch_runner.cpp)
target_link_libraries(sequencer_tests PRIVATE
        sequencer-tests-lib)


# building tests for utils
add_subdirectory(utils-and-constants)
add_executable(utils_tests
        catch_runner.cpp)
target_link_libraries(utils_tests PRIVATE
        utils-tests-lib)

# building tests for watchdog and redlines
add_subdirectory(watchdog)
add_executable(watchdog_tests
        catch_runner.cpp)
target_link_libraries(watchdog_tests PRIVATE
        watchdog-tests-lib)

# building tests for ecs
add_subdirectory(ecs)
add_executable(ecs_tests
        catch_runner.cpp)
target_link_libraries(ecs_tests PRIVATE
        ecs-tests-lib)

# building tests for everything
# if you add a new test lib, don't forget to add it here
add_executable(all_tests
        catch_runner.cpp)
target_link_libraries(all_tests PRIVATE
        phys-boundary-tests-lib
        sequencer-tests-lib
        utils-tests-lib
        watchdog-tests-lib
        comm-boundary-tests-lib
        ecs-tests-lib)
