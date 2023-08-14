add_compile_options("${WARNINGS_LIST}")

add_subdirectory(comm-boundary)
add_subdirectory(constants)
add_subdirectory(ecs)
add_subdirectory(logger)
add_subdirectory(phys-boundary)
add_subdirectory(sequencer)
add_subdirectory(utils)
add_subdirectory(watchdog)

