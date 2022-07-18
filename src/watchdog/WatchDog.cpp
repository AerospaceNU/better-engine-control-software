//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"

#include <utility>

WatchDog::WatchDog():
    WatchDog(std::vector<IRedline*>())
{
}

WatchDog::WatchDog(std::vector<IRedline*> conds):
    conditions(std::move(conds))
{}

std::vector<std::tuple<ECSRedLineResponse, IRedline*>> WatchDog::stepRedlines(SensorData& data){
    std::vector<std::tuple<ECSRedLineResponse, IRedline*>> result = {};

    for(IRedline* curTest : this->conditions){
        ECSRedLineResponse response = curTest->testCondition(data);

        if(response != ECSRedLineResponse::SAFE){
            result.emplace_back(response, curTest);
        }
    }

    return result;
}

void WatchDog::updateRedlines(std::vector<IRedline *>& newConds) {
    this->conditions = newConds;
}

