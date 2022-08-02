add_library(sequencer Sequencer.cpp)

add_subdirectory(sequences)
target_link_libraries(sequencer PUBLIC
        sequences)