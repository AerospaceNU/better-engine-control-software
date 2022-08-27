message(STATUS "Fetching LibSerial... (this will take a while)")


set(LIBSERIAL_ENABLE_TESTING OFF CACHE BOOL "Enables building unit tests" FORCE)
set(LIBSERIAL_BUILD_EXAMPLES OFF CACHE BOOL "Enables building example programs" FORCE)
set(LIBSERIAL_PYTHON_ENABLE OFF CACHE BOOL "Enables building the library with Python SIP bindings" FORCE)
set(LIBSERIAL_BUILD_DOCS OFF CACHE BOOL "Build the Doxygen docs" FORCE)
set(INSTALL_SHARED OFF CACHE BOOL "Install shared object library." FORCE)


#message(STATUS "LIBSERIAL_ENABLE_TESTING VAL: ${LIBSERIAL_ENABLE_TESTING}")
#option(LIBSERIAL_ENABLE_TESTING "Enables building unit tests" OFF)
#option(LIBSERIAL_BUILD_EXAMPLES "Enables building example programs" OFF)
#option(LIBSERIAL_PYTHON_ENABLE "Enables building the library with Python SIP bindings" OFF)
#option(LIBSERIAL_BUILD_DOCS "Build the Doxygen docs" OFF)

# make available
if (IS_CROSS)
    FetchContent_MakeAvailable(libserial)
endif()
