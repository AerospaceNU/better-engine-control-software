//
// Created by kevin on 12/7/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H

#include "redlines/IRedline.h"
#include "redlines/RedlineResponsePacket.h"
#include "utils/SensorData.h"
#include <etl/vector.h>

/**
 * A interface to monitor sensor data for abnormalities.
 */
class IWatchDog{
public:
    /**
     * Updates stored current redlines list
     */
    virtual void updateRedlines(etl::vector<std::unique_ptr<IRedline>, 45> newRedlines) = 0;

    /**
     * Runs passed sensor data through redlines list
     * @param data sensor data to check
     * @return list of tuples, each tuple being the failed redline's response, and the failed redline itself
     */
    virtual etl::vector<RedlineResponsePacket, 45> stepRedlines(const SensorData& data) = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IWATCHDOG_H
