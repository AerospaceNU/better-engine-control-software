cmake_minimum_required(VERSION 3.16)
project(better_engine_control_software)

# we are on C++17 because our current cross-compiler doesn't support 20. it would be beneficial if we could use 20
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# setting compiler flags (which are sadly specific to each compiler)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        # using GCC
        # from https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
        SET(GCC_FLAGS_LIST
                -Os # optimize for size, we can use -Oz for even more size optimization
                -Wall # general set of warnings
                -Wextra # extra warnings
                -Wfloat-equal # comparing floats directly for equality
                -Wundef # idk lol
                -Wcast-qual # removing type specifiers (ex. const) through casting
                -Wlogical-op # idk lol
                -Wmissing-declarations # for functions without a declaration
                -Wredundant-decls # if multiple declarations in same scope
                -Wshadow # if local var shadows another with the same name
                -Wsequence-point # weird unspecified order UB
                -Wno-psabi # gets rid of a really long warning in our external libraries
                # -Wpadded # warning about padding (might be useful for memory optimization later)
                )
        # CMake lists are basically just strings separated by semicolons, we want to replace them with plain spaces
        string (REPLACE ";" " " FORMATTED_GCC_FLAGS "${GCC_FLAGS_LIST}")

        SET(CMAKE_CXX_FLAGS ${FORMATTED_GCC_FLAGS})

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # using Clang
        # do jack for now
        # from https://clang.llvm.org/docs/DiagnosticsReference.html
        SET(Clang_FLAGS_LIST
                -Os # optimize for size, we can use -Oz for even more size optimization
                -Wall# general set of warnings
                -W # Synonym for -Wextra
                -Wfloat-equal # comparing floats directly for equality
                -Wundef # Warn if an undefined identifier is evaluated in an #if directive. Such identifiers are replaced with zero.
                -Wcast-qual # removing type specifiers (ex. const) through casting
                -Wparentheses # controls -Wbitwise-conditional-parentheses, -Wbitwise-op-parentheses, -Wdangling-else, -Wlogical-not-parentheses, -Wlogical-op-parentheses, -Woverloaded-shift-op-parentheses, -Wparentheses-equality, -Wshift-op-parentheses.
                -Wmissing-declarations # for functions without a declaration
                -Wredundant-move # redundant move in return statement
                -Wshadow-all # if local var shadows another with the same name
                -Wunsequenced # weird unspecified order UB
                -Wpadded # warning about padding (might be useful for memory optimization later)
                )
        string (REPLACE ";" " " FORMATTED_Clang_FLAGS "${Clang_FLAGS_LIST}")

        SET(CMAKE_CXX_FLAGS ${FORMATTED_Clang_FLAGS})

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # using Visual Studio C++
        # msvc specifies warning levels, not individual flags
        SET(MSVC_FLAGS_LIST
                /Os
                /Oy
                /Ob0
                /GF
                /Gy # above are all flags for size optimization
                /EHsc # weird exception thing
                /W4 # general warning set
                /permissive- # makes msvc warn about non-standard code
                )
        string (REPLACE ";" " " FORMATTED_MSVC_FLAGS "${MSVC_FLAGS_LIST}")

        SET(CMAKE_CXX_FLAGS ${FORMATTED_MSVC_FLAGS})
endif()

# TODO: consider options like -Werror
# this would require us to switch off warnings for our header libraries though
# this is fine, but compiler specific so we need a long term solution to support 3 compilers

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# this makes it so we can reference header files from the src/ folder, instead of a relative path
include_directories(src)

add_subdirectory(catch_tests)
add_subdirectory(src)
add_subdirectory(external)

add_executable(ecs_quick main_tweak.cpp)
target_link_libraries(ecs_quick PUBLIC
        watchdog
        constants)

add_executable(ecs_pi main_pi.cpp)

if (NOT IS_CROSS)
        find_package(PkgConfig)
        pkg_check_modules(SERIAL libserial)
endif()

target_link_libraries(ecs_pi PUBLIC
        json-comm
        horizontal-ecs
        # logger TODO get logger working again
        pi-boundary
        sequencer
        utils
        constants
        watchdog
        logger
        Threads::Threads
        # wtf are these i copied pasted it from the old ecs
        ${CMAKE_THREAD_LIBS_INIT})

add_executable(ecs_sim main_sim.cpp)
target_link_libraries(ecs_sim PUBLIC
        json-comm
        horizontal-ecs
        # logger TODO get logger working again
        sim-boundary
        sequencer
        utils
        constants
        watchdog
        logger
        Threads::Threads)

# just tinkering
# target_link_options(ecs_sim PRIVATE "/MAP:${PROJECT_SOURCE_DIR}/cmake-build-debug/ecs_sim.map")
