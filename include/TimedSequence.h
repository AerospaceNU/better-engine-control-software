//
// Created by Elyssa Adams on 4/4/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#include "generic/ISequence.h"
#include <vector>
#include <tuple>

class TimedSequence: public ISequence{
public:
    explicit TimedSequence(std::vector<std::tuple<ECSState, uint64_t>> seq);

    /**
     * Gets the state at a certain index of a sequence and the delta time associated with it.
     * @param index the index of the needed state
     * @return the state and the time offset
     */
    virtual std::tuple<ECSState, uint64_t> getStateTime(int index);

    virtual int length();

protected:
    std::vector<std::tuple<ECSState, uint64_t>> seq;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
