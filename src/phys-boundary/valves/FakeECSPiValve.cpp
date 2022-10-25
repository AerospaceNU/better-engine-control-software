//
// Created by David.L on 10/19/22.
//

#include "FakeECSPiValve.h"
#include <stdexcept>

FakeECSPiValve::FakeECSPiValve(ECSValveState initialState) :
        currentSTATE(initialState)
{
    if (initialState == ECSValveState::INVALID){
        throw std::runtime_error("Starting valid state cannot be INVALID");
    }
}

ECSValveState FakeECSPiValve::getValveState() {
    /*
     * FAKE
     */

    return this->currentSTATE;
}

void FakeECSPiValve::setValveState(ECSValveState newState) {
    /*
     * FAKE
    */
    if (newState != ECSValveState::OPEN && newState != ECSValveState::CLOSED){
        throw EffectorException{};
    }

    currentSTATE = newState;

}
