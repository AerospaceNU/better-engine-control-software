//
// Created by kevin on 6/1/2022.
//

#include "RelatTimedSequence.h"

RelatTimedSequence::RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState &>> *seq) :
        RelatTimedSequence(seq, 0) {}

RelatTimedSequence::RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState &>> *seq, int index) :
        waitTime(std::get<0>((*seq)[index])),
        storedState(std::get<1>((*seq)[index]))
{
    if (index >= seq->size()-1) {
        this->nextSeq = nullptr;
    } else { //is new the best choice? to be determined once i actually get c++
        this->nextSeq = new RelatTimedSequence(seq, index + 1);
    }
}

bool RelatTimedSequence::testCondition(uint64_t startTime, uint64_t curTime) const{
    return (curTime - startTime) >= this->waitTime;
}

ISequence* RelatTimedSequence::getNextSequence() const{
    return this->nextSeq;
}

ECSState& RelatTimedSequence::getStoredState() const{
    return this->storedState;
}
