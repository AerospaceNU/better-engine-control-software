//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include "phys-boundary/valves/ECSPiValve.h"
#include "phys-boundary/valves/ECSThreeWayPiValve.h"
//#include <libserial/SerialPort.h>

#include <cstring>
#include <chrono>
#include <stdexcept>
#include <utility>

TeensyBoundary::TeensyBoundary(LibSerial::SerialPort *adcPort,
                               LibSerial::SerialPort* tPort) :
        storedData(SensorData{}),
        sensorDataWriteMutex(),
        adcboardPort((adcPort)),
        teensyPort((tPort))
        // workerThread() // do not start thread in initializer list, valves haven't been set yet
        //TODO: inject the values from the constructor, that way it is safe to initalize in constructor
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

    // this->workerThread = std::jthread([this](std::stop_token token) {
    //     while(token.stop_requested()) {
    //         this->readPackets();
    //     }
    // });
}

SensorData TeensyBoundary::readFromBoundary() {
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //RAII goated

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


void TeensyBoundary::readFromTeensy(WrappedPacket &wrappedPacket) {
    // CRC is included, but we're not checking it for validity right now
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //use of RAII, that way mutex unlocks even if exceptions throw

    storedData.loadCell = wrappedPacket.dataPacket.loadCell0;

    // ln2 tank
    //dataStore->values["tank1Thermo"] = filterNan(wrappedPacket->dataPacket.tc0);
    storedData.loxTank1 = filterDoubleNan(wrappedPacket.dataPacket.tc0);
    // kero tank
    //dataStore->values["tank2Thermo"] = filterNan(wrappedPacket->dataPacket.tc1);
    storedData.loxTank2 = filterDoubleNan(wrappedPacket.dataPacket.tc1);
    // miscalleneous
    //dataStore->values["tank3Thermo"] = filterNan(wrappedPacket->dataPacket.tc2);
    storedData.loxTank3 = filterDoubleNan(wrappedPacket.dataPacket.tc2);
    //dataStore->values["loadCell"] = wrappedPacket->dataPacket.loadCell0;
}

void TeensyBoundary::readFromADCBoard(AdcBreakoutSensorData &adcPacket) {
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //use of RAII, that way mutex unlocks even if exceptions throw

    storedData.loxInletDucer = adcPacket.adc4;
    storedData.kerInletDucer = adcPacket.adc5;
    storedData.purgeDucer = adcPacket.adc6;
    storedData.kerPintleDucer = adcPacket.adc7;
    storedData.kerTankDucer = adcPacket.adc8;
    storedData.loxTankDucer = adcPacket.adc11;
    storedData.pnematicsDucer = adcPacket.adc10;
    storedData.loxVenturi = adcPacket.adc2;
    storedData.kerVenturi = adcPacket.adc3;

    // TODO: Determine which physical sensors these are
    // i have no clue what cam meant by the above comment and the following commented out code
    //dataStore->values["loxN2Ducer"] = 0;
    //dataStore->values["kerN2Ducer"] = 0;
}


void TeensyBoundary::readFromEffectors() {
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);

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

void TeensyBoundary::readPackets() {
    LibSerial::DataBuffer dataBuffer;

    {
        this->teensyPort->Read(dataBuffer, sizeof(WrappedPacket));
        uint8_t *rawDataBuffer = dataBuffer.data();

        WrappedPacket wPacket;
        std::memcpy(&wPacket, rawDataBuffer, sizeof wPacket);
        this->readFromTeensy(wPacket);
    }

    {
        this->adcboardPort->Read(dataBuffer, sizeof(AdcBreakoutSensorData));
        uint8_t *rawDataBuffer = dataBuffer.data();

        AdcBreakoutSensorData aPacket;
        std::memcpy(&aPacket, rawDataBuffer, sizeof aPacket);
        this->readFromADCBoard(aPacket);
    }

    this->readFromEffectors();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}


