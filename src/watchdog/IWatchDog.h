//
// Created by kevin on 12/7/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H

#include <vector>
#include "redlines/IRedline.h"
#include "redlines/RedlineResponsePacket.h"
#include "utils/SensorData.h"

/**
 * A interface to monitor sensor data for abnormalities.
 */
class IWatchDog{
public:
    /**
     * Updates stored current redlines list
     */
    virtual void updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) = 0;

    /**
     * Runs passed sensor data through redlines list
     * @param data sensor data to check
     * @return list of tuples, each tuple being the failed redline's response, and the failed redline itself
     */
    virtual std::vector<RedlineResponsePacket> stepRedlines(SensorData& data) = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H
