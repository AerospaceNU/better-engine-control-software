# i wanted to keep the libserial linking encapsulated in a library, but templates requrie just header files,
# cmake lets you build a target without soruce files if it's an INTERFACE library
add_library(serial-packets INTERFACE)

target_link_libraries(serial-packets INTERFACE CRC16 libserial_static)

