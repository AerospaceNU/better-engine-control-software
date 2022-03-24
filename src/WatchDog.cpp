//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"
#include <iostream>

WatchDog::WatchDog(std::vector<Redline> conditions){
    WatchDog::conditions = conditions;
}

bool WatchDog::stepRedlines(SensorData data){
    bool has_passed = true;

    for(int i = 0; i < this->conditions.size(); i++){
        Redline curTest = this->conditions[i];

        if(!curTest.testCondition(data)){
            has_passed = false;
            std::cout << curTest.name << std::endl;
        }
    }

    return has_passed;
}