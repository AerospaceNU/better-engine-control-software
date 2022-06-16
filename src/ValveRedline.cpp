//
// Created by allison on 4/13/2022.
//

#include "ValveRedline.h"
#include <stdexcept>
#include "utils-and-constants/ECSUtils.h"

ValveRedline::ValveRedline(std::string n, std::function<ECSValveState(const SensorData*)> sFunct, ECSValveState s):
        ValveRedline(n, sFunct, s, ECSRedLineResponse::WARN)
{}

ValveRedline::ValveRedline(std::string n, std::function<ECSValveState(const SensorData*)> sFunct,
                           ECSValveState s, ECSRedLineResponse res):
        IRedline(n, res),
        selector(sFunct),
        expectedState(s)
{}

bool ValveRedline::testCondition(const SensorData* data) const {
    return this->expectedState == this->selector(data);
}

std::string ValveRedline::errorMessage(const SensorData* data) const {
    std::string expected;
    if(this->expectedState == ECSValveState::OPEN){
        expected = "open";
    }
    else if(this->expectedState == ECSValveState::CLOSED){
        expected = "closed";
    }
    else{
        expected = "invalid";
    }

    std::string actual;
    if(this->selector(data) == ECSValveState::OPEN){
        actual = "open";
    }
    else if(this->selector(data) == ECSValveState::CLOSED){
        actual = "closed";
    }
    else{
        actual = "invalid";
    }

    return this->name + " failed, expected " + expected + " but was " + actual;
}

