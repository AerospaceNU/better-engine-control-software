//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include "phys-boundary/valves/ECSPiValve.h"
#include "phys-boundary/valves/ECSThreeWayPiValve.h"

#include <chrono>
#include <utility>

namespace{
    void updateFromPropBoard(SensorData& data, PropBoardSensorData& propPacket){
        static_assert(SensorData::majorVersion == 1,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        //TODO will likely require sensordata changes, update later
    }
}


TeensyBoundary::TeensyBoundary(std::unique_ptr<IPacketSource<PropBoardSensorData>> pSource,
                               std::vector<SensorDataCalibrator> cList) :
        calibratorList(std::move(cList)),
        storedData(),
        packetSource(std::move(pSource))
        //TODO: inject the valves from the constructor
{
    wiringPiSetupGpio();
    static_assert(CommandData::majorVersion == 1,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    // Instantiating Valves
    this->loxPressurant = new ECSPiValve(ECSValveState::CLOSED, 13);
    this->kerPressurant = new ECSPiValve(ECSValveState::CLOSED, 17);
    this->loxPurge = new ECSPiValve(ECSValveState::CLOSED, 22);
    this->kerPurge = new ECSPiValve(ECSValveState::CLOSED, 27);
    this->loxVent = new ECSPiValve(ECSValveState::OPEN, 5);
    this->kerVent = new ECSPiValve(ECSValveState::OPEN, 12);
    this->loxFlow = new ECSPiValve(ECSValveState::CLOSED, 6);
    // Special 3-way solenoid valve
    // Uses physical pins 13 and 15
    this->kerFlow = new ECSThreeWayPiValve(26, 19);

    this->loxDrip = new ECSPiValve(ECSValveState::CLOSED, 9);
    this->kerDrip = new ECSPiValve(ECSValveState::CLOSED, 10);
}

SensorData TeensyBoundary::readFromBoundary() {
    PropBoardSensorData pData = this->packetSource->getPacket();
    updateFromPropBoard(storedData, pData);

    this->readFromEffectors();

    for(auto& calibrator: this->calibratorList){
        calibrator.applyCalibration(storedData);
    }

    return this->storedData;
}

void TeensyBoundary::writeToBoundary(CommandData &data) {
    static_assert(CommandData::majorVersion == 1,
                  "Function not updated from CommandData change, please update this function and the static_assert");

    this->loxVent->setValveState(data.loxVent);
    this->kerVent->setValveState(data.kerVent);

    this->loxDrip->setValveState(data.loxDrip);
    this->kerDrip->setValveState(data.kerDrip);

    this->loxPressurant->setValveState(data.loxPressurant);
    this->kerPressurant->setValveState(data.kerPressurant);

    this->loxFlow->setValveState(data.loxFlow);
    this->kerFlow->setValveState(data.kerFlow);

    this->loxPurge->setValveState(data.loxPurge);
    this->kerPurge->setValveState(data.kerPurge);
}


void TeensyBoundary::readFromEffectors() {
    static_assert(CommandData::majorVersion == 1,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    storedData.loxVent = this->loxVent->getValveState();
    storedData.kerVent = this->kerVent->getValveState();
    storedData.loxDrip = this->loxDrip->getValveState();
    storedData.kerDrip = this->kerDrip->getValveState();
    storedData.loxPressurant = this->loxPressurant->getValveState();
    storedData.kerPressurant = this->kerPressurant->getValveState();
    storedData.loxFlow = this->loxFlow->getValveState();
    storedData.kerFlow = this->kerFlow->getValveState();
    storedData.loxPurge = this->loxPurge->getValveState();
    storedData.kerPurge = this->kerPurge->getValveState();
}



