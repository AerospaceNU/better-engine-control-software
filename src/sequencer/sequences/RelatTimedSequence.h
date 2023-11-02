//
// Created by Elyssa Adams on 4/4/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H

#include "sequencer/sequences/ISequence.h"
#include <vector>
#include <utility>
#include <memory>

/**
 * Implementation of ISequence. Stores time delay as relative millisecond delay between consecutive states
 */
class RelatTimedSequence: public ISequence{
public:
    /*
     * All sequences are initialized on startup. If we ever need to create new
     * sequences during the runtime of the program, then we will need to revisit
     * all the places we store pointers/references to sequences to make sure they
     * stay valid
     */
    /**
     * Implements sequence as a linked list data structure
     *
     * @param seq list of tuples representing milliseconds to wait before a
     * transition, and the state to transition to
     *
     * ex: [(10, ONLINE_SAFE), (20, HECK)] means after 10 milliseconds, transition
     * to ONLINE_SAFE, after 20 milliseconds, transition to HECK
     *
     * ex: To initialize class do
     * RelatTimedSequence seq{{{100, state}, {100, state}, {100, state}}};
     *
     * @throws std::out_of_range if seq is empty
     */
    explicit RelatTimedSequence(etl::vector<std::pair<uint64_t, ECSState>, 30> seq);

    /*
     * deleting the copy/move constructors that way we don't accidently make new sequences
     */
    RelatTimedSequence(const RelatTimedSequence& other) = delete;
    RelatTimedSequence(RelatTimedSequence&& other) = delete;
    RelatTimedSequence& operator=(const RelatTimedSequence& other) = delete;

    bool testCondition(uint64_t startTime, uint64_t curTime) override;
    ECSState getStoredState() override;
    ISequence* getNextSequence() override;

private:
    //NOTE: keep this constructor as a separate private constructor, rather than have index with a default arg
    RelatTimedSequence(etl::vector<std::pair<uint64_t, ECSState>, 30>& seq , size_t index);

    uint64_t waitTime;
    ECSState storedState;
    std::unique_ptr<ISequence> nextSeq;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_RELAT_SEQUENCE_H
