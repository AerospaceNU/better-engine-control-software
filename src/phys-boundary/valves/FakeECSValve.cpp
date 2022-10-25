//
// Created by David.L on 10/19/22.
//

#include "FakeECSValve.h"
#include <stdexcept>

FakeECSValve::FakeECSValve(ECSValveState initialState) :
        currentSTATE(initialState)
{
    if (initialState == ECSValveState::INVALID){
        throw std::runtime_error("Starting valid state cannot be INVALID");
    }
}

ECSValveState FakeECSValve::getValveState() {
    /*
     * FAKE
     */

    return this->currentSTATE;
}

void FakeECSValve::setValveState(ECSValveState newState) {
    /*
     * FAKE
    */
    if (newState != ECSValveState::OPEN && newState != ECSValveState::CLOSED){
        throw EffectorException{"Command was invalid!"};
    }

    currentSTATE = newState;
}
