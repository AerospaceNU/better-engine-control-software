//
// Created by kevin on 3/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include "ECSUtils.h"
#include "Redline.h"
#include "SensorData.h"
#include "WatchDogRedlines.h"

class WatchDog{
public:
    // WatchDog(std::vector<Redline*> conds);
    std::vector<Redline*> conditions = ONLINE_SAFE_D;

    void updateRedlines(std::vector<Redline*>);
    std::vector<Redline*> stepRedlines(SensorData* data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
