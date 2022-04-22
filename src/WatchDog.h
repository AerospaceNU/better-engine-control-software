//
// Created by kevin on 3/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include "Redline.h"
#include "SensorData.h"
#include <vector>
#include "IntWithinRedline.h"
#include "ValveRedline.h"
#include "ECSUtils.h"
#include "WatchDogRedlines.h"

class WatchDog{
public:
    // WatchDog(std::vector<Redline*> conds);
    std::vector<Redline*> conditions = ONLINE_SAFE_D;

    std::vector<Redline*> stepRedlines(SensorData* data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
