//
// Created by kevin on 6/1/2022.
//

#include "sequencer/sequences/RelatTimedSequence.h"

RelatTimedSequence::RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState &>>& seq) :
        RelatTimedSequence(seq, 0) {}

RelatTimedSequence::RelatTimedSequence(std::vector<std::tuple<uint64_t, ECSState &>>& seq, int index) :
        waitTime(std::get<0>(seq[index])),
        storedState(std::get<1>(seq[index]))
{
    if (index >= seq.size()-1) {
        this->nextSeq = std::unique_ptr<ISequence>(nullptr);
    } else {
        this->nextSeq = std::unique_ptr<ISequence>(new RelatTimedSequence(seq, index + 1));
    }
}

bool RelatTimedSequence::testCondition(uint64_t startTime, uint64_t curTime) {
    return (curTime - startTime) >= this->waitTime;
}

ISequence* RelatTimedSequence::getNextSequence() {
    return this->nextSeq.get();
}

ECSState& RelatTimedSequence::getStoredState() {
    return this->storedState;
}
