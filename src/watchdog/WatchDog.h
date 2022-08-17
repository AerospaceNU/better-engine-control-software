#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H

#include <vector>
#include <tuple>
#include "watchdog/redlines/IRedline.h"
#include "utils/SensorData.h"

/**
 * A class to monitor sensor data for abnormalities.
 */
class WatchDog{
public:
    WatchDog();
    explicit WatchDog(std::vector<IRedline*>  conds);

    /**
     * Updates stored current redlines list
     */
    void updateRedlines(std::vector<IRedline*>&);

    /**
     * Runs passed sensor data through redlines list
     * @param data sensor data to check
     * @return list of tuples, each tuple being the failed redline's response, and the failed redline itself
     */
    std::vector<std::tuple<ECSRedLineResponse, IRedline*>> stepRedlines(SensorData& data);

private:
    std::vector<IRedline*> conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOG_H
