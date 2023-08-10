# the expected cmakelist also give additional build targets that we switch off here
set(BUILD_TESTING OFF CACHE BOOL "Enables building unit tests" FORCE)
set(EXPECTED_BUILD_PACKAGE OFF CACHE BOOL "Enables building the package for various Linux distros" FORCE)

add_subdirectory(expected)
