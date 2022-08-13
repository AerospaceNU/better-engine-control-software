//
// Created by Elyssa Adams on 4/4/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H

#include "sequencer/sequences/ISequence.h"
#include <vector>
#include <tuple>
#include <memory>

/**
 * Implementation of ISequence. Stores time delay as relative millisecond delay between consecutive states
 */
class RelatTimedSequence: public ISequence{
public:
    /*
     * All sequencer are initialized on startup. If we ever need to create new
     * sequencer during the runtime of the program, then we will need to revisit
     * all the places we store pointers/references to sequencer to make sure they
     * stay valid
     */
    explicit RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState&>>& seq);

    //delete copy and copy assignment operators
    RelatTimedSequence(const RelatTimedSequence& other) = delete;
    RelatTimedSequence& operator=(const RelatTimedSequence& other) = delete;

    bool testCondition(uint64_t startTime, uint64_t curTime) override;
    ECSState& getStoredState() override;
    ISequence* getNextSequence() override;

private:
    //NOTE: keep this constructor as a separate private constructor, rather than have index with a default arg
    RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState&>>& seq , int index);

    uint64_t waitTime;
    ECSState& storedState;
    std::unique_ptr<ISequence> nextSeq;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H
