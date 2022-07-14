//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include "utils-and-constants/SensorData.h"

SensorData FakeBoundary::readFromBoundary(){
    return this->curData;
}

void FakeBoundary::writeToBoundary(CommandData& cmdData){
    this->curData.loxVent = cmdData.loxVent;
    this->curData.kerVent = cmdData.kerVent;
    this->curData.loxDrip = cmdData.loxDrip;
    this->curData.kerDrip = cmdData.kerDrip;
    this->curData.loxPressurant = cmdData.loxPressurant;
    this->curData.kerPressurant = cmdData.kerPressurant;
    this->curData.loxFlow = cmdData.loxFlow;
    this->curData.kerFlow = cmdData.kerFlow;
    this->curData.loxPurge = cmdData.loxPurge;
    this->curData.kerPurge = cmdData.kerPurge;
}