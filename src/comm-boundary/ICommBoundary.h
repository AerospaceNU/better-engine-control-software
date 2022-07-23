//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H

//#include "ecs/IECS.h"
#include "utils-and-constants/CommandData.h"
#include <vector>
#include <tuple>
#include "watchdog/IRedline.h"

#include "utils-and-constants/SensorData.h"
#include "utils-and-constants/ECSState.h"

//TODO: why do we need this
class IECS; //WHAT THE FUCK?????

class ICommBoundary{
public:
    virtual void reportState(ECSState& curState) = 0;
    virtual void reportRedlines(std::tuple<ECSRedLineResponse, IRedline*>) = 0;
    virtual void reportSensorData(SensorData data) = 0;
    virtual void reportMessage(std::string msg) = 0;

    virtual void acceptECS(IECS& ecs) = 0;

    virtual void run() = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
