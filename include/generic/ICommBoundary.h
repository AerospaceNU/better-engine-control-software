//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#include "CommandData.h"
#include "SensorData.h"

class ICommBoundary{
    virtual void sendToECS(CommandData* data) = 0;
    virtual void sendToUser(SensorData* data) = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
