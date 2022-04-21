//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"
#include <iostream>

//WatchDog::WatchDog(std::vector<Redline*> conds){
//    this->conditions = conds;
//}

std::vector<Redline*> WatchDog::stepRedlines(SensorData* data){
    std::vector<Redline*> result = {};

    for(Redline* curTest : this->conditions){
        if(!curTest->testCondition(data)){
            result.push_back(curTest);
            //log into logger
            std::cout << curTest->errorMessage(data) << std::endl;
        }
    }

    return result;
}