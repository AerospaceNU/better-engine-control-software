//
// Created by kevin on 4/11/2022.
//

#include "IntWithinRedline.h"

IntWithinRedline::IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int uBound, int lBound):
    name(n),
    selector(sFunct),
    upperBound(uBound),
    lowerBound(lBound)
{}

bool IntWithinRedline::checkWithin(int num){
    return (this->lowerBound < num) and (num < this->upperBound);
}

bool IntWithinRedline::testCondition(SensorData* data){
    return this->checkWithin(this->selector(data));
}