//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include "SensorData.h"

SensorData* FakeBoundary::readFromBoundary(){
    return new SensorData(42);
}

bool FakeBoundary::writeToBoundary(CommandData cmdData){
    return false;
}