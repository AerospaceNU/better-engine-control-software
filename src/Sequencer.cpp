//
// Created by Neel Sortur on 4/25/22.
//

#include "Sequencer.h"

Sequencer::Sequencer(uint64_t startTime):
    currSequence(nullptr),
    ogStartTime(startTime),
    startTime(startTime)
{}



void Sequencer::startSequence(uint64_t startTime, ISequence *seq){
    this->ogStartTime = startTime;
    this->startTime = startTime;

    this->currSequence = seq;
}

ECSState* Sequencer::stepSequence(uint64_t currTime) {
    if(!this->sequenceRunning()){
        //do some type of alert
        //throw an exception? we can just them ppl when using "hey, call sequenceRunning() first!"
        //std::cout << "Sequence has not been set" << std::endl;
        return nullptr;
    }

    if(this->currSequence->testCondition(this->startTime, currTime)){
        ECSState& result = this->currSequence->getStoredState();
        this->currSequence = this->currSequence->getNextSequence();
        this->startTime = currTime;

        //wtf?
        return &result;
    }

    return nullptr;
}

bool Sequencer::sequenceRunning() {
    return this->currSequence;
}


void Sequencer::abortSequence() {
    this->currSequence = nullptr;
}



