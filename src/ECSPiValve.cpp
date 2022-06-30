//
// Created by Cameron on 5/13/21.
//

#include "ECSPiValve.h"

ECSPiValve::ECSPiValve(ECSValveState initialState, int pinNumber) :
    defaultState(initialState),
    pinNumber(pinNumber)
{
    pinMode(this->pinNumber, OUTPUT);
}

ECSValveState ECSPiValve::getValveState() {
    /*
     * HIGH and LOW are determined by the default state of the valve.
     * If the pin is HIGH then we must be in the opposite of the default state.
     * Likewise, if the pin is LOW we can just automatically return the default
     * state of the valve.
     */
    int pinReadout = digitalRead(this->pinNumber);

    if (pinReadout == 1) {
        if (this->defaultState == ECSValveState::OPEN) {
            return ECSValveState::CLOSED;
        } else {
            return ECSValveState::OPEN;
        }
    } else {
        return this->defaultState;
    }

}

void ECSPiValve::setValveState(ECSValveState newState) {
    // std::cout << "Entering ECSPiValve setValveState()"  << this->elementLabel << std::endl;

    /*
     * HIGH and LOW are determined by the default state of the valve.
     * If the default is CLOSED and we want to set the valve into a CLOSED state
     * we send a LOW signal. Likewise, if the default is OPEN and we set the valve to OPEN
     * it should still send a LOW signal. The HIGH signal will be sent if trying to set the
     * valve state to the opposite of the default.
     */

    switch (newState) {
        case ECSValveState::OPEN:
            if (this->defaultState == ECSValveState::OPEN) {
                digitalWrite(this->pinNumber, LOW);
            } else {
                digitalWrite(this->pinNumber, HIGH);
            }
            break;
        case ECSValveState::CLOSED:
            if (this->defaultState == ECSValveState::CLOSED) {
                digitalWrite(this->pinNumber, LOW);
            } else {
                digitalWrite(this->pinNumber, HIGH);
            }
            break;
        default:
            throw std::runtime_error("Tried to set valve to an unrecognized state (neither open or closed");
    }
}
