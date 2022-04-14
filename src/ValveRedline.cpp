//
// Created by allison on 4/13/2022.
//

#include "IntWithinRedline.h"
#include <stdexcept>

ValveRedline::ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct, ECSValveState state):
        Redline(n),
        selector(sFunct),
        ECSValveState(state)


bool ValveWithinRedline::checkSame(ECSValveState s){
    return this->lowerBound = s;
}

bool IntWithinRedline::testCondition(SensorData* data){
    return this->checkSame(this->selector(data));
}

