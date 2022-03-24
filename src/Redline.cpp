//
// Created by kevin on 3/23/2022.
//

#include "Redline.h"
Redline::Redline(std::string name, int upperLimit, int lowerLimit) {

    this->name = name;
    this->upperLimit = upperLimit;
    this->lowerLimit = lowerLimit;
}

bool Redline::testCondition(SensorData data){
    return true;
}