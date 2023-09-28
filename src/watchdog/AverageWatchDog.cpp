//
// Created by eric on 9/27/2022.
//

#include "AverageWatchDog.h"
#include "utils/SensorDataUtils.h"
#include <utility>

AverageWatchDog::AverageWatchDog(std::vector<std::unique_ptr<IRedline>> conds):
    conditions()
{
    for(auto& redline: conds){
        if(redline){
            this->conditions.emplace_back(std::move(redline));
        }
    }
}

std::vector<RedlineResponsePacket> AverageWatchDog::stepRedlines(const SensorData& data){
    std::vector<RedlineResponsePacket> result = {};

    this->dataHistory.push_front(data);

    for(auto& curTest : this->conditions){
        SensorData averaged = averageData({dataHistory.begin(), dataHistory.end()});

        ECSRedLineResponse response = curTest->testCondition(averaged);

        result.emplace_back(response, curTest->getName());
    }

    return result;
}

void AverageWatchDog::updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) {
    this->conditions.clear();
    this->dataHistory.clear();

    for(auto& redline: newRedlines){
        if(redline){
            conditions.emplace_back(std::move(redline));
        }
    }
}

