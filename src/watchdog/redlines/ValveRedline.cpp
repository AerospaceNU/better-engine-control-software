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

std::string ValveRedline::getName() const{
    return this->name;
}

ECSRedLineResponse ValveRedline::testCondition(SensorData& data) {
    if (this->expectedState == this->selector(data)){
        return ECSRedLineResponse::SAFE;
    }
    return this->response;
}


std::unique_ptr<IRedline> ValveRedline::clone() {
    return std::make_unique<ValveRedline>(*this);
}

std::unique_ptr<ValveRedline> RedlineFactory(std::string n,
                                             std::function<ECSValveState(SensorData&)>& sFunct,
                                             ECSValveState state,
                                             ECSRedLineResponse res) {
    return std::make_unique<ValveRedline>(std::move(n), sFunct, state, res);
}

