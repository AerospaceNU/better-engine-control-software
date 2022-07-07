//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include "utils-and-constants/SensorData.h"

SensorData FakeBoundary::readFromBoundary(){
    return SensorData{};
}

bool FakeBoundary::writeToBoundary(CommandData cmdData){
    return true;
}