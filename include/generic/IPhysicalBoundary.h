#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H


#include "SensorData.h"
#include "CommandData.h"

/**
 * An IPhysicalBoundary is an abstraction for an object that reads sensor data
 * and activates effectors (ex. valves). This can be for the test-stand
 * or the actual rocket.
 */
class IPhysicalBoundary{
public:
    /**
     * Returns the latest sensor data.
     * @return a SensorData object
     */
    virtual SensorData readFromBoundary() = 0;

    /**
     * Sets the effectors to the given configuration
     * @param data command data representing the configuration we want
     * @throws exception [type to be specified later] if writing fails (valves don't work, etc)
     */
    virtual void writeToBoundary(CommandData data) = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H