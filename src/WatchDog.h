//
// Created by kevin on 3/23/2022.
//
#include "Redline.h"
#include "SensorData.h"
#include <vector>

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

class WatchDog{
public:
    WatchDog(std::vector<Redline> conditions);
    std::vector<Redline> conditions;
    bool stepRedlines(SensorData data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
