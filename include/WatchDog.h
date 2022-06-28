#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include "generic/IRedline.h"
#include "SensorData.h"
#include "utils-and-constants/HorizontalECSRedlines.h"

/**
 * A class to monitor sensor data for abnormalities.
 */
class WatchDog{
public:
    explicit WatchDog(std::vector<IRedline*>* conds);

    /**
     * Updates stored current redlines list
     */
    void updateRedlines(std::vector<IRedline*>*);

    /**
     * Runs passed sensor data through redlines list
     * @param data sensor data to check
     * @return list of failed redlines
     */
    std::vector<IRedline*> stepRedlines(SensorData* data);

protected:
    std::vector<IRedline*>* conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
