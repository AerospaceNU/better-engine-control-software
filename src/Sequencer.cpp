//
// Created by Neel Sortur on 4/25/22.
//

#include "Sequencer.h"

const uint64_t TOO_MUCH_TIME = 100;

Sequencer::Sequencer()
{}

/*
Sequencer::Sequencer(IECS *ecs) {
    this->index = 0;
    this->startOfCurrStateTime = 0;
    this->running = false;
    this->currSequence = nullptr;
    this->lastSequence = nullptr;
    this->ecs = ecs;
}*/

void Sequencer::startSequence(uint64_t startTime, ISequence *seq){
    /*
    this->index = 0;
    this->startOfCurrStateTime = startTime;
    this->currSequence = seq;
    this->running = true;
    std::tuple<ECSState, uint64_t> startingState = this->currSequence->getStateTime(this->index);
    std::cout << "Sequence started" << std::endl;
    std::cout << "Entering state: " << ECSStateToStringMap[std::get<0>(startingState)] << std::endl;
    this->ecs->setState(std::get<0>(startingState));
     */
}

ECSState Sequencer::stepSequence(uint64_t currTime) {
    /*
    // TODO make enum return type
    if (!this->running) {
        std::cout << "Sequence has not been set" << std::endl;
        return;
    }
    if (this->index == this->currSequence->length() - 1) {
        std::cout << "Sequence finished successfully" << std::endl;
        this->endSequence();
        return;
    }
    std::tuple<ECSState, uint64_t> currState = this->currSequence->getStateTime(this->index);
    uint64_t relTime = std::get<1>(currState);
    uint64_t endStateTime = this->startOfCurrStateTime + relTime;
    if (endStateTime <= currTime && (currTime - endStateTime < TOO_MUCH_TIME)) {
        // if the current time surpassed the time the sequence should be set, and it's not too late
        this->index = this->index + 1;
        this->startOfCurrStateTime = currTime;
        std::tuple<ECSState, uint64_t> nextState = this->currSequence->getStateTime(this->index);
        std::cout << "Entering state: " << ECSStateToStringMap[std::get<0>(nextState)] << std::endl;
        this->ecs->setState(std::get<0>(nextState));
    }
     */
    return ONLINE_SAFE;
}

bool Sequencer::sequenceRunning() {
    return this->running;
}


void Sequencer::abortSequence() {
    //TODO: bruh
}


void Sequencer::endSequence() {
    this->currSequence = nullptr;
    this->running = false;
}

