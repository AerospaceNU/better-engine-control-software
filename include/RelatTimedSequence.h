//
// Created by Elyssa Adams on 4/4/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#include "generic/ISequence.h"
#include <vector>
#include <tuple>

class RelatTimedSequence: public ISequence{
public:
    explicit RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState&>>* seq);

    bool testCondition(uint64_t startTime, uint64_t curTime) override;
    ECSState& getStoredState() override;
    ISequence* getNextSequence() override;

protected:
    RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState&>>* seq , int index);

    uint64_t waitTime;
    ECSState& storedState;
    ISequence* nextSeq;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
