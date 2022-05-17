#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H

#include "SensorData.h"
#include "CommandData.h"

class IBoundary{
public:

    /*
     * Reads sensor input data from boundary
     */
    virtual SensorData* readFromBoundary(int counter) = 0;

    /*
     * Sends commands to control engine
     */
    virtual bool writeToBoundary(CommandData data) = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H