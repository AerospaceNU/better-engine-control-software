//
// Created by kevin on 2/23/2022.
//

#include "SensorData.cpp"
#include "CommandData.cpp"
#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_BOUNDARY_H

class Boundary{
public:
    /*
     * Reads sensor input data from boundary
     */
    virtual SensorData readFromBoundary() = 0;

    /*
     * Sends commands to control engine
     */
    virtual bool writeToBoundary(CommandData data) = 0;
};