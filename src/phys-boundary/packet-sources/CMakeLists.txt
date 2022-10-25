# i wanted to keep the libserial linking encapsulated in a library, but you can't build
# header only libraries
# so i just have a dummy file
add_library(serial-packets
        DummySource.cpp FakeIPacketSource.h)

if (IS_CROSS)
    target_link_libraries(serial-packets PUBLIC libserial_static)
endif()