//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include "SensorData.h"

SensorData* FakeBoundary::readFromBoundary(){
    return new SensorData(1,2,3,4);
}

bool FakeBoundary::writeToBoundary(CommandData cmdData){
    return true;
}