//
// Created by Cameron on 7/13/21.
//

#include "ECSThreeWayPiValve.h"
#include <wiringPi.h>

ECSThreeWayPiValve::ECSThreeWayPiValve(int topPinNum, int botPinNum) :
    topPinNumber(topPinNum),
    botPinNumber(botPinNum)
{
    pinMode(this->topPinNumber, OUTPUT);
    pinMode(this->botPinNumber, OUTPUT);
}


ECSValveState ECSThreeWayPiValve::getValveState() {
    // TODO: Need to know the difference between the different states
    /*
     * HIGH (represented as 1) and LOW (represented as 0)
     */
    int topReadout = digitalRead(this->topPinNumber);
    int botReadout = digitalRead(this->botPinNumber);

    if (topReadout == 0 && botReadout == 0) {
        return ECSValveState::INVALID; // This will probably break stuff
    } else if (topReadout == 0 && botReadout == 1) {
        return ECSValveState::CLOSED;
    } else if (topReadout == 1 && botReadout == 0) {
        return ECSValveState::OPEN;
    } else if (topReadout == 1 && botReadout == 1) {
        return ECSValveState::INVALID;
        //throw std::runtime_error("Should never be in state where both pins are 1 of three-position solenoid");
    } else {
        // Should literally never happen
        return ECSValveState::INVALID;
        //throw std::runtime_error("Invalid pin readouts (not a valid combination of 0 and 1s????");
    }
}


void ECSThreeWayPiValve::setValveState(ECSValveState newState) {
    switch (newState) {
        case ECSValveState::OPEN:
            // Open if the top is high and bottom is low
            // Counting in binary this state = 2 (10)
            digitalWrite(this->topPinNumber, HIGH);
            digitalWrite(this->botPinNumber, LOW);
            break;

        case ECSValveState::CLOSED:
            // Closed if the top is low and bottom is high
            // Counting in binary this stae = 1 (01)
            digitalWrite(this->topPinNumber, LOW);
            digitalWrite(this->botPinNumber, HIGH);
            break;

        default:
            std::string msg = "Three way valve with top pin number: "
                    + std::to_string(topPinNumber)
                    + " and bottom pin number: "
                    + std::to_string(botPinNumber)
                    + " failed actuation!";
            throw EffectorException{msg};
    }
}
