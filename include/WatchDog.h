#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include "generic/IRedline.h"
#include "SensorData.h"
#include "utils-and-constants/HorizontalECSRedlines.h"

class WatchDog{
public:

    explicit WatchDog(const std::vector<const IRedline*>* conds);

    void updateRedlines(const std::vector<const IRedline*>*);
    std::vector<const IRedline*> stepRedlines(const SensorData* data);

protected:
    const std::vector<const IRedline*>* conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
