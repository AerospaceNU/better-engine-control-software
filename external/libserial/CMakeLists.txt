# the actual libserial repo gets put elsewhere, personally for me i found it in cmake-build-debug/_deps

message(STATUS "Fetching LibSerial... (this will take a while)")

# the libserial cmakelist also give build targets for generating its documentation
# and tests. we switch these flags off so that it doesn't do that
set(LIBSERIAL_ENABLE_TESTING OFF CACHE BOOL "Enables building unit tests" FORCE)
set(LIBSERIAL_BUILD_EXAMPLES OFF CACHE BOOL "Enables building example programs" FORCE)
set(LIBSERIAL_PYTHON_ENABLE OFF CACHE BOOL "Enables building the library with Python SIP bindings" FORCE)
set(LIBSERIAL_BUILD_DOCS OFF CACHE BOOL "Build the Doxygen docs" FORCE)
set(INSTALL_SHARED OFF CACHE BOOL "Install shared object library." FORCE)


# make available
# we have to surround this in an block, bc libserial adds gcc compiler flags to the cmake
# if you aren't using gcc, then cmake will error
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    FetchContent_MakeAvailable(libserial)
endif()
