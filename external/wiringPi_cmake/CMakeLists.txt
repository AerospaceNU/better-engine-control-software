# this is actually a patch of WiringPi. WiringPi has been abandoned by the original creator, but there's still
# a GitHub mirror of the source. this guy patched the build system to be CMake instead of Makefiles, so we're using
# his branch

# it's worth mentioning that wiringPi is a LGPL library
# if you don't know what GPL is, it's a famous open source license for projects. the gimmick is copyleft,
# if your project uses a GPL library, you have to make your own project GPL/open source as well
# LGPL is a bit different though. if you link to a shared library which is LGPL, you are still clear,
# and wiringPi builds as a shared library

# plus the ECS is licensed under GPL so we're double fine

# yeah, wiringPi compiles with these warnings triggering, which are enabled by default
# which is worrying, but fuck fixing that
add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-Wno-int-to-pointer-cast;-Wno-pointer-to-int-cast;-Wno-unused-result>")
add_subdirectory(WiringPi)
