//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#include "CommandData.h"
#include <vector>
#include <tuple>
#include "generic/IRedline.h"

#include "SensorData.h"

class ICommBoundary{
    virtual void reportState(std::string curState) = 0;
    virtual void reportRedlines(std::vector<std::tuple<ECSRedLineResponse, IRedline*>>) = 0;
    virtual void reportSensorData(SensorData data) = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
