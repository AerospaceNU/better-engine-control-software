//
// Created by kevin on 3/23/2022.
//

#include "WatchDog.h"

#include <utility>

WatchDog::WatchDog(std::vector<std::unique_ptr<IRedline>> conds, unsigned int cap):
    conditions(std::move(conds)),
    storageCap(cap)
{}

std::vector<std::pair<ECSRedLineResponse, std::unique_ptr<IRedline>>> WatchDog::stepRedlines(SensorData& data){
    std::vector<std::pair<ECSRedLineResponse, std::unique_ptr<IRedline>>> result = {};

    if (this->storageCap > this->sensData.size()) {
        this->sensData.push_back(data);
    }

    for(auto& curTest : this->conditions){
        ECSRedLineResponse response = curTest->testCondition(data);

        if(response != ECSRedLineResponse::SAFE){
            result.emplace_back(response, curTest->clone());
        }
    }

    return result;
}

void WatchDog::updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) {
    this->conditions = std::move(newRedlines);
    this->sensData.clear();
}

