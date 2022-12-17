add_library(sequencer-tests-lib OBJECT
        RelatTimedSequenceTests.cpp SequencerTests.cpp HangingSequence.cpp)

target_link_libraries(sequencer-tests-lib PUBLIC
        sequencer
        constants)