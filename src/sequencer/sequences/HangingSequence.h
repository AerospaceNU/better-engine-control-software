//
// Created by kevin on 12/7/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HANGINGSEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HANGINGSEQUENCE_H
#include "ISequence.h"
#include <stdexcept>

/**
 * An implementation of an ISequence that doesn't contain any
 * ECSStates at all, but will always return false when asked if ready to transition
 *
 * In short, this is meant to hang
 *
 * Useful for unit testing
 */
class HangingSequence: public ISequence{
public:
    /**
     * Always returns false
     * @param startTime ignored
     * @param curTime ignored
     * @return false
     */
    bool testCondition(uint64_t startTime, uint64_t curTime) override;

    /**
     * ALWAYS Throws an exception
     * @throws std::out_of_range
     */
    ECSState getStoredState() override;

    /**
     * Returns nullptr
     * @return nullptr
     */
    ISequence* getNextSequence() override;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HANGINGSEQUENCE_H
