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
    return this->state == this->selector(data);//this->checkSame(this->selector(data));
}

std::string ValveRedline::errorMessage(SensorData* data){
    std::string expected;
    if(this->state == OPEN){
        expected = "open";
    }else if(this->state == CLOSED){
        expected = "closed";
    }else{
        expected = "invalid";
    }
    std::string actual;
    if(this->selector(data) == OPEN){
        actual = "open";
    }else if(this->selector(data) == CLOSED){
        actual = "closed";
    }else{
        actual = "invalid";
    }
    return this->name + " failed, expected " + expected + "but was " + actual;
}

