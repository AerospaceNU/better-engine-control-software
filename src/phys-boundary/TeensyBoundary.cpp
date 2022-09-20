//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include "phys-boundary/valves/ECSPiValve.h"
#include "phys-boundary/valves/ECSThreeWayPiValve.h"

#include <cstring>
#include <chrono>
#include <stdexcept>
#include <utility>

namespace{
    /**
     * Updates the given sensor data for load cell and TC data packet
     *
     * @param data sensor data object to update
     * @param wrappedPacket reference to data packet from serial packet
     */
    void updateFromTeensy(SensorData& data, TeensyData& dataPacket){
        data.loadCell = dataPacket.loadCell0;

        // ln2 tank
        //dataStore->values["tank1Thermo"] = filterNan(wrappedPacket->dataPacket.tc0);
        data.loxTank1 = filterDoubleNan(dataPacket.tc0);
        // kero tank
        //dataStore->values["tank2Thermo"] = filterNan(wrappedPacket->dataPacket.tc1);
        data.loxTank2 = filterDoubleNan(dataPacket.tc1);
        // miscalleneous
        //dataStore->values["tank3Thermo"] = filterNan(wrappedPacket->dataPacket.tc2);
        data.loxTank3 = filterDoubleNan(dataPacket.tc2);
        //dataStore->values["loadCell"] = wrappedPacket->dataPacket.loadCell0;
    }

    /**
     * Updates the given sensor data to pressurant data from packet
     *
     * @param data sensor data object to update
     * @param adcPacket reference to data packet from serial packet
     */
    void updateFromADC(SensorData& data, AdcBreakoutSensorData& adcPacket){
        data.loxInletDucer = adcPacket.adc4;
        data.kerInletDucer = adcPacket.adc5;
        data.purgeDucer = adcPacket.adc6;
        data.kerPintleDucer = adcPacket.adc7;
        data.kerTankDucer = adcPacket.adc8;
        data.loxTankDucer = adcPacket.adc11;
        data.pnematicsDucer = adcPacket.adc10;
        data.loxVenturi = adcPacket.adc2;
        data.kerVenturi = adcPacket.adc3;

        // TODO: Determine which physical sensors these are
        // i have no clue what cam meant by the above comment and the following commented out code
        //dataStore->values["loxN2Ducer"] = 0;
        //dataStore->values["kerN2Ducer"] = 0;
    }
}


TeensyBoundary::TeensyBoundary(ADCPacketSource adcSrc,
                               TeensyPacketSource tSrc,
                               std::vector<SensorDataCalibrator> cList) :
        calibratorList(std::move(cList)),
        storedData(),
        adcSource(std::move(adcSrc)),
        teensySource(std::move(tSrc))
        //TODO: inject the valves from the constructor
{
    wiringPiSetupGpio();
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

    // if we ever get to use C++20, replace the above def with this

//    this->workerThread = std::jthread([this](std::stop_token token) {
//        while(token.stop_requested()) {
//            this->readPackets();
//        }
//    });
}

SensorData TeensyBoundary::readFromBoundary() {
    TeensyData tData = this->teensySource.getPacket();
    updateFromTeensy(storedData, tData);

    AdcBreakoutSensorData aData = this->adcSource.getPacket();
    updateFromADC(storedData, aData);

    this->readFromEffectors();

    for(auto& calibrator: this->calibratorList){
        calibrator.applyCalibration(storedData);
    }

    return this->storedData;
}

void TeensyBoundary::writeToBoundary(CommandData &data) {
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



