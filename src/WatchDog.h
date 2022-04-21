//
// Created by kevin on 3/23/2022.
//
#include "Redline.h"
#include "SensorData.h"
#include <vector>
#include "FakeRedline1.h"
#include "IntWithinRedline.h"
#include "ValveRedline.h"
#include "ECSUtils.h"

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

class WatchDog{
public:
    // WatchDog(std::vector<Redline*> conds);
    std::vector<Redline*> conditions = {new IntWithinRedline("test1",
                                                             [](SensorData* data){return data->sensor1Data;},
                                                             6, 9),
                                        new IntWithinRedline("test2",
                                                             [](SensorData* data){return data->sensor2Data;},
                                                             10, 15),
                                        new IntWithinRedline("test3",
                                                             [](SensorData* data){return data->sensor2Data;},
                                                             1, 3),
                                        new ValveRedline("test4",
                                                         [](SensorData* data){return data->loxVent;},
                                                         OPEN)
                                        };

    std::vector<Redline*> stepRedlines(SensorData* data);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
