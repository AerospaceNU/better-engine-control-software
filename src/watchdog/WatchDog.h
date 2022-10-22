#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include <utility>
#include "watchdog/redlines/IRedline.h"
#include "utils/SensorData.h"

/**
 * A class to monitor sensor data for abnormalities.
 */
class WatchDog{
public:
    explicit WatchDog(std::vector<IRedline*> conds = {}, int cap = 1);

    /**
     * Updates stored current redlines list
     */
    void updateRedlines(std::vector<IRedline*> newRedlines);

    /**
     * Runs passed sensor data through redlines list
     * @param data sensor data to check
     * @return list of tuples, each tuple being the failed redline's response, and the failed redline itself
     */
    std::vector<std::pair<ECSRedLineResponse, IRedline*>> stepRedlines(SensorData& data);

private:
    std::vector<IRedline*> conditions;
    std::vector<SensorData> sensData;
    int storageCap;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
