//
// Created by kevin on 6/1/2022.
//

#include "sequencer/sequences/RelatTimedSequence.h"
#include <utility>
#include <etl/vector.h>

RelatTimedSequence::RelatTimedSequence(etl::vector<std::pair<uint64_t, ECSState>, 30> seq) :
        RelatTimedSequence(seq, 0) {}

//private constructor, the usage of moving from a vector reference is justified here since it is encapsulated
RelatTimedSequence::RelatTimedSequence(etl::vector<std::pair<uint64_t, ECSState>, 30>& seq, size_t index) :
        waitTime(seq.at(index).first), //use .at() instead of [] for bounds checking
        storedState(std::move(seq.at(index).second))
{
    if (index >= seq.size()-1) {
        this->nextSeq = std::unique_ptr<ISequence>(nullptr);
    } else {
        //can't use make_unique, constructor is private
        this->nextSeq = std::unique_ptr<ISequence>(new RelatTimedSequence(seq, index + 1));
    }
}

bool RelatTimedSequence::testCondition(uint64_t startTime, uint64_t curTime) {
    // important guard against integer underflow
    if (startTime > curTime){
        return false;
    }

    return (curTime - startTime) >= this->waitTime;
}

ISequence* RelatTimedSequence::getNextSequence() {
    return this->nextSeq.get();
}

ECSState RelatTimedSequence::getStoredState() {
    return this->storedState;
}
