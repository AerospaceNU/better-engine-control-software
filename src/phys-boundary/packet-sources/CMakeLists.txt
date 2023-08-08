# i wanted to keep the libserial linking encapsulated in a library, but you can't build
# header only libraries
# so i just have a dummy file
add_library(serial-packets INTERFACE)

if (IS_CROSS)
    target_link_libraries(serial-packets INTERFACE libserial_static)
endif()
