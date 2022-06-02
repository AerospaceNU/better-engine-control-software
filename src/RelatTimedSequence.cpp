//
// Created by kevin on 6/1/2022.
//

#include "RelatTimedSequence.h"

RelatTimedSequence::RelatTimedSequence(const std::vector<std::tuple<uint64_t, ECSState &>> *seq) :
        RelatTimedSequence(seq, 0) {}

RelatTimedSequence::RelatTimedSequence(const std::vector<std::tuple<uint64_t, ECSState &>> *seq, int index) :
        timeWait(std::get<0>((*seq)[index])),
        storedState(std::get<1>((*seq)[index]))
{
    if (index >= seq->size()) {
        this->nextSeq = nullptr;
    } else { //is new the best choice? to be determined once i actually get c++
        this->nextSeq = new RelatTimedSequence(seq, index + 1);
    }
}

bool RelatTimedSequence::testCondition(uint64_t startTime, uint64_t curTime) const{
    return (curTime - startTime) >= this->timeWait;
}

const ISequence* RelatTimedSequence::getNextSequence() const{
    return this->nextSeq;
}

const ECSState& RelatTimedSequence::getStoredState() const{
    return this->storedState;
}
