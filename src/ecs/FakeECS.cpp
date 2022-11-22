//
// Created by kevin on 9/29/2022.
//

#include "FakeECS.h"

void FakeECS::acceptStartSequence([[maybe_unused]] ISequence &seq) {
    this->sequenceStarted = true;
}

void FakeECS::acceptStateTransition([[maybe_unused]] ECSState &newState) {
    this->stateChanged = true;
}

void FakeECS::acceptOverrideCommand([[maybe_unused]] CommandData commands) {
    this->overrideCalled = true;
}

void FakeECS::acceptAbortSequence() {
    this->abortSequenceCalled = true;
}


void FakeECS::acceptAbort() {
    this->abortCalled = true;
}
