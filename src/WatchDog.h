//
// Created by kevin on 3/23/2022.
//
#include "Redline.h"
#include "SensorData.h"
#include <vector>
#include "FakeRedline1.h"

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

class WatchDog{
public:
    // WatchDog(std::vector<Redline*> conds);
    std::vector<Redline*> conditions = {new FakeRedline1()};
    bool stepRedlines(SensorData* data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
