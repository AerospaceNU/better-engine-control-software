#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include "generic/IRedline.h"
#include "SensorData.h"
#include "utils-and-constants/HorizontalECSRedlines.h"

class WatchDog{
public:

    explicit WatchDog(std::vector<IRedline*>* conds);

    void updateRedlines(std::vector<IRedline*>*);
    std::vector<IRedline*> stepRedlines(SensorData* data);

protected:
    std::vector<IRedline*>* conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
