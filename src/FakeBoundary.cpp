//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include "SensorData.h"

SensorData* FakeBoundary::readFromBoundary(int counter){
    return new SensorData(counter);
}

bool FakeBoundary::writeToBoundary(CommandData cmdData){
    return true;
}