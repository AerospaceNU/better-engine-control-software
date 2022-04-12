//
// Created by kevin on 4/11/2022.
//
#include "IntWithinRedline.h"
#include <stdexcept>

IntWithinRedline::IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int lBound, int uBound):
    Redline(n),
    selector(sFunct),
    lowerBound(lBound),
    upperBound(uBound)
{
    if (lBound > uBound){
        throw std::invalid_argument("Lower bound cannot be greater than upper bound");
    }
}

bool IntWithinRedline::checkWithin(int num){
    return (this->lowerBound < num) and (num < this->upperBound);
}

bool IntWithinRedline::testCondition(SensorData* data){
    return this->checkWithin(this->selector(data));
}