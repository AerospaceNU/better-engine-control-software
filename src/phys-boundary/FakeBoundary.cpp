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

/**
 * need to hit every single field from the CommandData
 */
FakeBoundary::FakeBoundary() {
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
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
    this->curData.kerOrifice = ECSValveState::CLOSED;
}

/**
 * need to hit every single field from the SensorData
 */
SensorData FakeBoundary::readFromBoundary(){
    static_assert(SensorData::majorVersion == 7,
                  "Function not updated from SensorData change, please update this function and the static_assert");
    this->curData. loxTankDucer = generateRandom(100, 200);
    // this->curData. kerTankDucer = generateRandom(100, 200);
    // this->curData. purgeDucer = generateRandom(100, 200);
    // this->curData. loxInletDucer = generateRandom(100, 200);
    this->curData. kerInletDucer = generateRandom(100, 200);
    this->curData. kerPintleDucer = generateRandom(100, 200);
    this->curData. loxVenturi = generateRandom(100, 200);
    this->curData. loxVenturi2 = generateRandom(100, 200);
    this->curData. kerVenturi = generateRandom(100, 200);
    this->curData. kerVenturi2 = generateRandom(100, 200);

    this->curData. pneumaticDucer = generateRandom(100, 200);

    this->curData. loadCell = generateRandom(100, 200);

    this->curData. loxTankTC = generateRandom(100, 200);
    this->curData. kerInletTC = generateRandom(100, 200);
    this->curData. kerOutletTC = generateRandom(100, 200);
    this->curData. miscTC = generateRandom(100, 200);

    this->curData. loxRegDucer = generateRandom(100, 200);
    this->curData. kerRegDucer = generateRandom(100, 200);
    // this->curData. n2pressDucer = generateRandom(100, 200);
    this->curData. orificeUpstreamDucer = generateRandom(100, 200);

    this->curData. loxTankTC = generateRandom(100, 200);
    this->curData. kerInletTC = generateRandom(100, 200);
    this->curData. kerOutletTC = generateRandom(100, 200);
    this->curData. miscTC = generateRandom(100, 200);

    this->curData.boardTemp = generateRandom(100,200);

    this->curData.kerInletTC_Fault = 0;
    this->curData.kerOutletTC_Fault = 0;
    this->curData.loxTankTC_Fault = 0;
    this->curData.miscTC_Fault = 0;

    return this->curData;
}

/**
 * need to hit every single field from the CommandData
 */
void FakeBoundary::writeToBoundary(const CommandData& cmdData){
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");

    if (cmdData.loxVent == ECSValveState::INVALID or
        cmdData.kerVent == ECSValveState::INVALID or
        cmdData.loxDrip == ECSValveState::INVALID or
        cmdData.kerDrip == ECSValveState::INVALID or
        cmdData.loxPressurant == ECSValveState::INVALID or
        cmdData.kerPressurant == ECSValveState::INVALID or
        cmdData.loxFlow == ECSValveState::INVALID or
        cmdData.kerFlow == ECSValveState::INVALID or
        cmdData.loxPurge == ECSValveState::INVALID or
        cmdData.kerPurge == ECSValveState::INVALID or
        cmdData.kerOrifice == ECSValveState::INVALID
    ){
        throw EffectorException{"Input CommandData cannot have INVALID as a config"};
    }

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
    this->curData.kerOrifice = cmdData.kerOrifice;
}


