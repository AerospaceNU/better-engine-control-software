//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#include "utils-and-constants/CommandData.h"
#include <vector>
#include <tuple>
#include "watchdog/IRedline.h"

#include "utils-and-constants/SensorData.h"

class ICommBoundary{
    virtual void reportState(std::string curState) = 0;
    virtual void reportRedlines(std::vector<std::tuple<ECSRedLineResponse, IRedline*>>) = 0;
    virtual void reportSensorData(SensorData data) = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
