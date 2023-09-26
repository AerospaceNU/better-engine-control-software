cmake_minimum_required(VERSION 3.16)
project(better_engine_control_software)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


cmake_policy(SET CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if( supported )
        message(STATUS "IPO / LTO enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        cmake_policy(SET CMP0069 NEW) 
        set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
else()
        message(STATUS "IPO / LTO not supported: <${error}>")
endif()

# GLOBAL COMPILER FLAGS
# flags belong here if they CAN and SHOULD be applied to all code (includes tests and external dependencies)
# ex. optimization flags
# flags also belong here if they only work correctly if applied to all code
# ex. flags removing runtime type info, sanitizer flags
add_compile_options(
        # msvc requires a flag to specify how to handle exceptions???
        "$<$<CXX_COMPILER_ID:MSVC>:/EHsc>"

        # optimize for smaller binary size
        "$<$<CXX_COMPILER_ID:GNU>:-Os>" # we can use -Oz for even more size optimization
        "$<$<CXX_COMPILER_ID:Clang>:-Os>" # we can use -Oz for even more size optimization
        "$<$<CXX_COMPILER_ID:MSVC>:/Os;/Oy;/Ob0;/GF;/Gy>"

        # get rid of runtime type support
        # removes type info, saves space but can't use dynamic_cast and shit
        # TODO: uncomment these out when we move away from libserial, which uses dynamic_cast
        # "$<$<CXX_COMPILER_ID:GNU>:-fno-rtti>"
        # "$<$<CXX_COMPILER_ID:Clang>:-fno-rtti>"
        # "$<$<CXX_COMPILER_ID:MSVC>:/GR>"
)



# WARNING FLAGS
# warning flags are not global, bc they shouldn't be run on our external dependencies
#       if they are run, best case they cause a lot of noise that can obscure new warnings,
#       worse case compilation fails bc we error on warnings for some compilers

# create our warning flags for our three supported compilers, GCC, Clang, and MSVC
# you shouldn't need to use the private_*_WARNINGS_LIST vars directly, they are compiler 
# specific
string(JOIN ";" private_GCC_WARNINGS_LIST
                -Wall # general set of warnings
                -Wextra # extra warnings
                -Wcatch-value=2 # class types that are caught by value
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
                # -march=native
                -Wpedantic # stricter warnings on non cross platform code
                -Werror # makes warnings errors, the final frontier
                )
string(JOIN ";" private_CLANG_WARNINGS_LIST
                -Wall# general set of warnings
                -Wextra # extra warnings
                -Wfloat-equal # comparing floats directly for equality
                -Wundef # Warn if an undefined identifier is evaluated in an #if directive. Such identifiers are replaced with zero.
                -Wcast-qual # removing type specifiers (ex. const) through casting
                -Wparentheses # controls -Wbitwise-conditional-parentheses, -Wbitwise-op-parentheses, -Wdangling-else, -Wlogical-not-parentheses, -Wlogical-op-parentheses, -Woverloaded-shift-op-parentheses, -Wparentheses-equality, -Wshift-op-parentheses.
                -Wmissing-declarations # for functions without a declaration
                -Wredundant-move # redundant move in return statement
                -Wshadow-all # if local var shadows another with the same name
                -Wunsequenced # weird unspecified order UB
                # -Wpadded # warning about padding (might be useful for memory optimization later)
                -Wpedantic # stricter warnings on non cross platform code
                -Wold-style-cast # warn on old C-style casts
                -Werror # makes warnings errors, the final frontier
                -Wpointer-arith # bad pointer arithmetic
                -Wpessimizing-move # bad moves
                -Wunused-variable # unused variable, either cast to void or use [[maybe_unused]]
                )
string(JOIN ";" private_MSVC_WARNINGS_LIST # msvc specifies warning levels, not individual flags
                /W4 # general warning set
                /permissive- # makes msvc warn about non-standard code
                # /WX # makes warnings errors # cannot currently use this flag,
                # msvc warns on external libs for some reason
                )

# warnings list to use, will apply correct set of flags depending on current compiler 
set(WARNINGS_LIST
        "$<$<CXX_COMPILER_ID:GNU>:${private_GCC_WARNINGS_LIST}>"
        "$<$<CXX_COMPILER_ID:Clang>:${private_CLANG_WARNINGS_LIST}>"
        "$<$<CXX_COMPILER_ID:MSVC>:${private_MSVC_WARNINGS_LIST}>")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# this makes it so we can reference header files with respect to the src/ folder, instead of a relative path
include_directories(src)

# when adding a new subdirectory, don't forget to compile it with WARNINGS_LIST if appropriate
add_subdirectory(catch_tests)
add_subdirectory(src)
add_subdirectory(external)

add_executable(ecs_quick main_tweak.cpp)
target_link_libraries(ecs_quick PUBLIC
        watchdog
        constants)

add_executable(ecs_pi main_pi.cpp)
target_compile_options(ecs_pi PRIVATE
        "${WARNINGS_LIST}")
target_link_libraries(ecs_pi PUBLIC
        json-comm
        stand-ecs
        pi-boundary
        sequencer
        utils
        fake-watchdog
        logger)
target_link_libraries(ecs_pi PRIVATE
        constants
        Threads::Threads
        atomic # need libatomic to be manually linked in
        wiringPi # need the wiringPiSetupGpio() function
        # wtf are these i copied pasted it from the old ecs
        ${CMAKE_THREAD_LIBS_INIT})

add_executable(ecs_sim main_sim.cpp)
target_compile_options(ecs_sim PRIVATE
        "${WARNINGS_LIST}")
target_link_libraries(ecs_sim PUBLIC
        json-comm
        stand-ecs
        sim-boundary
        sequencer
        utils
        fake-watchdog
        logger)
target_link_libraries(ecs_sim PRIVATE
        constants
        Threads::Threads)

# just tinkering
# target_link_options(ecs_sim PRIVATE "/MAP:${PROJECT_SOURCE_DIR}/cmake-build-debug/ecs_sim.map")
