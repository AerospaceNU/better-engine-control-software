add_library(sequencer-tests-lib OBJECT
        RelatTimedSequenceTests.cpp SequencerTests.cpp HangingSequenceTests.cpp)

target_link_libraries(sequencer-tests-lib PRIVATE
        sequencer
        fake-sequences
        constants)
