//
// Created by kevin on 12/7/2022.
//

#include "HangingSequence.h"


bool HangingSequence::testCondition([[maybe_unused]] uint64_t startTime, [[maybe_unused]] uint64_t curTime) {
    return false;
}

ECSState HangingSequence::getStoredState() {
    throw std::out_of_range{"bruh"};
}

ISequence *HangingSequence::getNextSequence() {
    return nullptr;
}
