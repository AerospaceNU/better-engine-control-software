//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"
#include <iostream>

//WatchDog::WatchDog(std::vector<Redline*> conds){
//    this->conditions = conds;
//}

bool WatchDog::stepRedlines(SensorData* data){
    bool has_passed = true;

    for(Redline* curTest : this->conditions){
        if(!curTest->testCondition(data)){
            has_passed = false;
            std::cout << curTest->name + " has failed" << std::endl;
        }
    }

    return has_passed;
}