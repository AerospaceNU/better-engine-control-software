//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H

#include "utils/ECSUtils.h"
#include "utils/ECSState.h"
#include <cstdint>

/*
 * sequencer need to
 * transition based on time
 * need to tell when the end of a sequence has been reached
 *
 * if we want to keep sequencer as a data type, then it shouldn't hold mutating state
 *
 * a type of linked list?
 * stepSequence(pastTime, curTime, (sensordata in the future?)
 *
 * ending sequence
 *
 */

/**
 * An abstraction for a node in a sequence of chained ECS states, separated by time delays
 */
class ISequence{
public:
    /**
     * Returns whether or not this sequence is ready to be advanced
     * @param startTime the last time a sequence was advanced
     * @param curTime current time
     * @return true if ready, false otherwise
     */
    virtual bool testCondition(uint64_t startTime, uint64_t curTime) = 0;

    /**
     * Returns the stored ECS state at this point in the sequence
     * @return a reference to the stored state
     */
    virtual ECSState& getStoredState() = 0;

    /**
     * Gets the next node in the sequence after this node
     * @return nullptr if this node is the last, else returns a valid ptr
     */
    virtual ISequence* getNextSequence() = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~ISequence() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
