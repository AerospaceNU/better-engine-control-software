//
// Created by allison on 4/13/2022.
//

#include "ValveRedline.h"
#include <stdexcept>
#include <utility>


ValveRedline::ValveRedline(std::string n, std::function<ECSValveState(SensorData&)>& sFunct,
                           ECSValveState expectedS, ECSRedLineResponse res):
        name(std::move(n)),
        selector(sFunct),
        expectedState(expectedS),
        response(res)
{}

std::string ValveRedline::getName() {
    return this->name;
}

ECSRedLineResponse ValveRedline::testCondition(SensorData& data) {
    if (this->expectedState == this->selector(data)){
        return ECSRedLineResponse::SAFE;
    }
    return this->response;
}

std::string ValveRedline::errorMessage(SensorData& data) {
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


