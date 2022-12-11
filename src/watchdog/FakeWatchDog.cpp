//
// Created by kevin on 3/23/2022.
//

#include "FakeWatchDog.h"
#include <utility>

FakeWatchDog::FakeWatchDog(std::vector<std::unique_ptr<IRedline>> conds):
    conditions()
{
    for(auto& redline: conds){
        if(redline){
            this->conditions.emplace_back(std::move(redline));
        }
    }
}

std::vector<RedlineResponsePacket> FakeWatchDog::stepRedlines(const SensorData& data){
    std::vector<RedlineResponsePacket> result = {};

    for(auto& curTest : this->conditions){
        ECSRedLineResponse response = curTest->testCondition(data);

        result.emplace_back(response, curTest->getName());
    }

    return result;
}

void FakeWatchDog::updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) {
    this->conditions.clear();

    for(auto& redline: newRedlines){
        if(redline){
            conditions.emplace_back(std::move(redline));
        }
    }
}

