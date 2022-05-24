//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_COMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_COMMBOUNDARY_H
#include "CommandData.h"
#include "SensorData.h"

class CommBoundary{
    virtual void sendToECS(CommandData* data);
    virtual void sendToUser(SensorData* data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_COMMBOUNDARY_H
