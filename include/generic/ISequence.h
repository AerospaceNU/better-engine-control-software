//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H

#include "utils-and-constants/ECSUtils.h"
#include "utils-and-constants/ECSState.h"
#include <stdint.h>

/*
 * sequences need to
 * transition based on time
 * need to tell when the end of a sequence has been reached
 *
 * if we want to keep sequences as a data type, then it shouldn't hold mutating state
 *
 * a type of linked list?
 * stepSequence(pastTime, curTime, (sensordata in the future?)
 *
 * ending sequence
 *
 *
 */
class ISequence{
public:
    virtual bool testCondition(uint64_t startTime, uint64_t curTime) const;
    virtual const ECSState& getStoredState() const;
    virtual const ISequence* getNextSequence() const;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
