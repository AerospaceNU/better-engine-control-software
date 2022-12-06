//
// Created by Neel Sortur on 4/25/22.
//

#include "Sequencer.h"

Sequencer::Sequencer():
    currSequence(nullptr),
    startTime(0)
{}



void Sequencer::startSequence(uint64_t sTime, ISequence& seq){
    this->startTime = sTime;

    this->currSequence = &seq;
}

std::optional<ECSState> Sequencer::stepSequence(uint64_t currTime) {
    if(!this->sequenceRunning()){
        return {};
    }

    if(this->currSequence->testCondition(this->startTime, currTime)){
        auto result = this->currSequence->getStoredState();
        this->currSequence = this->currSequence->getNextSequence();
        this->startTime = currTime;

        return result;
    }

    return {};
}

bool Sequencer::sequenceRunning() {
    return this->currSequence;
}


void Sequencer::abortSequence() {
    this->currSequence = nullptr;
}



