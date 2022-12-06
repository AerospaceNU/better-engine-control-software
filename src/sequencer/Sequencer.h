//
// Created by Neel Sortur on 4/25/22.
//

#ifndef ENGINECONTROLSYSTEM_SEQUENCER_H
#define ENGINECONTROLSYSTEM_SEQUENCER_H

#include "sequencer/sequences/ISequence.h"
#include <optional>

class Sequencer {
public:
    explicit Sequencer();

    /**
     * Starts a sequence given the starting time.
     * @param sTime The time value that indicates when the sequence should start
     * @param seq The sequence to be started by the Sequencer
     * @return
     */
    void startSequence(uint64_t sTime, ISequence& seq);

    /**
     * Aborts the current sequence that is being run by stopping at the current state and
     * abandoning the subsequent states
     * @return
     */
    void abortSequence();

    /**
     * Checks if a sequence has been started and is not over
     * @return if a sequence is currently running
     */
    bool sequenceRunning();


    /**
     * Steps through the sequence given the current time, either remaining at the current
     * state or moving on to the next in the sequence.
     * @param currTime The current time in the program we are running, the ECS time
     * @return ECSState, if the sequence transition is not satisfied IT WILL NOT HAVE A VALUE
     */
    std::optional<ECSState> stepSequence(uint64_t currTime);

private:
    ISequence* currSequence;
    uint64_t startTime;
};

#endif //ENGINECONTROLSYSTEM_SEQUENCER_H
