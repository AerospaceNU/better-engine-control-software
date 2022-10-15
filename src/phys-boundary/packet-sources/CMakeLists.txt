add_library(serial-packets
        ADCPacketSource.cpp
        TeensyPacketSource.cpp
        )

if (IS_CROSS)
    target_link_libraries(serial-packets PUBLIC libserial_static)
endif()