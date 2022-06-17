//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"


WatchDog::WatchDog(std::vector<IRedline*>* conds):
    conditions(conds)
{}

std::vector<IRedline*> WatchDog::stepRedlines(SensorData* data){
    std::vector<IRedline*> result = {};

    for(IRedline* curTest : *this->conditions){
        if(!curTest->testCondition(data)){
            result.push_back(curTest);
            //log into logger
            //std::cout << curTest->errorMessage(data) << std::endl;
        }
    }
    return result;
}

void WatchDog::updateRedlines(std::vector<IRedline *>* newConds) {
    this->conditions = newConds;
}
