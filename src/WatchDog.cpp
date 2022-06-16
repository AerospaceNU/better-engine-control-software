//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"
#include <iostream>


WatchDog::WatchDog(const std::vector<const IRedline*>* conds):
    conditions(conds)
{}

std::vector<const IRedline*> WatchDog::stepRedlines(const SensorData* data){
    std::vector<const IRedline*> result = {};

    for(const IRedline* curTest : *this->conditions){
        if(!curTest->testCondition(data)){
            result.push_back(curTest);
            //log into logger
            std::cout << curTest->errorMessage(data) << std::endl;
        }
    }
    return result;
}

void WatchDog::updateRedlines(const std::vector<const IRedline *>* newConds) {
    this->conditions = newConds;
}
