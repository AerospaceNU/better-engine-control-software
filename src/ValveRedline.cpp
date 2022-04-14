//
// Created by allison on 4/13/2022.
//

#include "ValveRedline.h"
#include <stdexcept>
#include "ECSUtils.h"

ValveRedline::ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct, ECSValveState s):
        Redline(n),
        selector(sFunct),
        state(s)
{}


//bool ValveRedline::checkSame(ECSValveState s){
 //   return this->state = s;
//}

bool ValveRedline::testCondition(SensorData* data){
    return this->state = this->selector(data);//this->checkSame(this->selector(data));
}

