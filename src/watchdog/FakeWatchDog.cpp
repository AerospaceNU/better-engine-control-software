//
// Created by kevin on 3/23/2022.
//

#include "FakeWatchDog.h"
#include <utility>

FakeWatchDog::FakeWatchDog(std::vector<std::unique_ptr<IRedline>> conds):
    conditions(std::move(conds))
{}

std::vector<RedlineResponsePacket> FakeWatchDog::stepRedlines(SensorData& data){
    std::vector<RedlineResponsePacket> result = {};

    for(auto& curTest : this->conditions){
        ECSRedLineResponse response = curTest->testCondition(data);

        result.emplace_back(response, curTest->getName());
    }

    return result;
}

void FakeWatchDog::updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) {
    this->conditions = std::move(newRedlines);
}

