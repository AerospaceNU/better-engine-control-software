#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include "generic/IRedline.h"
#include "SensorData.h"
#include "utils-and-constants/WatchDogRedlines.h"

class WatchDog{
public:
    WatchDog(std::vector<IRedline*> conds);

    void updateRedlines(std::vector<IRedline*>);
    std::vector<IRedline*> stepRedlines(const SensorData* data);

protected:
    std::vector<IRedline*> conditions = ONLINE_SAFE_D;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
