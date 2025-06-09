//
// Created by kevin on 3/23/2022.
//

#include "FakeWatchDog.h"
#include <utility>

FakeWatchDog::FakeWatchDog(etl::vector<std::unique_ptr<IRedline>, 45> conds):
    conditions()
{
    for(auto& redline: conds){
        if(redline){
            this->conditions.emplace_back(std::move(redline));
        }
    }
}

etl::vector<RedlineResponsePacket, 45> FakeWatchDog::stepRedlines(const SensorData& data){
    etl::vector<RedlineResponsePacket, 45> result = {};

    for(auto& curTest : this->conditions){
        ECSRedLineResponse response = curTest->testCondition(data);

        result.emplace_back(response, curTest->getName());
    }

    return result;
}

void FakeWatchDog::updateRedlines(etl::vector<std::unique_ptr<IRedline>, 45> newRedlines) {
    this->conditions.clear();

    for(auto& redline: newRedlines){
        if(redline){
            conditions.emplace_back(std::move(redline));
        }
    }
}

