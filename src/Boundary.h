//
// Created by kevin on 2/23/2022.
//

#pragma once
#include "SensorData.cpp"
#include "CommandData.cpp"


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