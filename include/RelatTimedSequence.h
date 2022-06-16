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
    explicit RelatTimedSequence(const std::vector<std::tuple<uint64_t, const ECSState&>>* seq);

    bool testCondition(uint64_t startTime, uint64_t curTime) const override;
    const ECSState& getStoredState() const override;
    const ISequence* getNextSequence() const override;

protected:
    RelatTimedSequence(const std::vector<std::tuple<uint64_t, const ECSState&>>* seq , int index);

    uint64_t waitTime;
    const ECSState& storedState;
    ISequence* nextSeq;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
