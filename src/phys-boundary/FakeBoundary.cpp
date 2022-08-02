//
// Created by kevin on 2/23/2022.
//

#include "FakeBoundary.h"
#include <cstdlib>

//helper functions
namespace{
    int generateRandom(int lowerBound, int upperBound) {
        return std::rand() % (upperBound - lowerBound) + lowerBound;
    }
}

FakeBoundary::FakeBoundary() {
    this->curData.loxVent = ECSValveState::CLOSED;
    this->curData.kerVent = ECSValveState::CLOSED;
    this->curData.loxDrip = ECSValveState::CLOSED;
    this->curData.kerDrip = ECSValveState::CLOSED;
    this->curData.loxPressurant = ECSValveState::CLOSED;
    this->curData.kerPressurant = ECSValveState::CLOSED;
    this->curData.loxFlow = ECSValveState::CLOSED;
    this->curData.kerFlow = ECSValveState::CLOSED;
    this->curData.loxPurge = ECSValveState::CLOSED;
    this->curData.kerPurge = ECSValveState::CLOSED;
}

SensorData FakeBoundary::readFromBoundary(){
    this->curData. loxTankDucer = generateRandom(100, 200);
    this->curData. kerTankDucer = generateRandom(100, 200);
    this->curData. purgeDucer = generateRandom(100, 200);
    this->curData. loxInletDucer = generateRandom(100, 200);
    this->curData. kerInletDucer = generateRandom(100, 200);
    this->curData. kerPintleDucer = generateRandom(100, 200);
    this->curData. loxVenturi = generateRandom(100, 200);
    this->curData. kerVenturi = generateRandom(100, 200);

    this->curData. pnematicsDucer = generateRandom(100, 200);

    this->curData. loadCell = generateRandom(100, 200);

    this->curData. loxTank1 = generateRandom(100, 200);
    this->curData. loxTank2 = generateRandom(100, 200);
    this->curData. loxTank3 = generateRandom(100, 200);
    this->curData. loxDripLine = generateRandom(100, 200);
    this->curData. outsideThroat = generateRandom(100, 200);
    this->curData. nozzle = generateRandom(100, 200);
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


