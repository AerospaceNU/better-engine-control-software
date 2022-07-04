//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include <stdexcept>
#include <utility>

TeensyBoundary::TeensyBoundary(std::string serial_port) :
        teensyPort(std::move(serial_port)),
        storedData(SensorData{}),
        m_member_thread(std::thread([this] { this->continuousSensorRead();}))
{
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
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //RAII goated

    return this->storedData;
}

void TeensyBoundary::writeToBoundary(CommandData data) {
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


void TeensyBoundary::readFromPacket(WrappedPacket* wrappedPacket) {
    // CRC is included, but we're not checking it for validity right now

    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //use of RAII, that way mutex unlocks even if exceptions throw

    storedData.loxInletDucer = wrappedPacket->dataPacket.adc4;
    storedData.kerInletDucer = wrappedPacket->dataPacket.adc5;
    storedData.purgeDucer = wrappedPacket->dataPacket.adc6;
    storedData.kerPintleDucer = wrappedPacket->dataPacket.adc7;
    storedData.kerTankDucer = wrappedPacket->dataPacket.adc8;
    storedData.loxTankDucer = wrappedPacket->dataPacket.adc11;
    storedData.pnematicsDucer = wrappedPacket->dataPacket.adc10;

    // TODO: Determine which physical sensors these are
    // i have no clue what cam meant by the above comment and the following commented out code
    //dataStore->values["loxN2Ducer"] = 0;
    //dataStore->values["kerN2Ducer"] = 0;

    storedData.loxVenturi = wrappedPacket->dataPacket.adc2;
    storedData.kerVenturi = wrappedPacket->dataPacket.adc3;

    storedData.loadCell = wrappedPacket->dataPacket.loadCell0;

    // ln2 tank
    //dataStore->values["tank1Thermo"] = filterNan(wrappedPacket->dataPacket.tc0);
    storedData.loxTank1 = filterNan(wrappedPacket->dataPacket.tc0);
    // kero tank
    //dataStore->values["tank2Thermo"] = filterNan(wrappedPacket->dataPacket.tc1);
    storedData.loxTank2 = filterNan(wrappedPacket->dataPacket.tc1);
    // miscalleneous
    //dataStore->values["tank3Thermo"] = filterNan(wrappedPacket->dataPacket.tc2);
    storedData.loxTank3 = filterNan(wrappedPacket->dataPacket.tc2);
    //dataStore->values["loadCell"] = wrappedPacket->dataPacket.loadCell0;
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

void TeensyBoundary::continuousSensorRead() {
    // Instantiate a SerialPort object.
    LibSerial::SerialPort serial_port;

    try {
        // Open the Serial Port at the desired hardware port.
        serial_port.Open(this->teensyPort);
    }
    catch (const LibSerial::OpenFailed &) {
        //std::cerr << "The serial port did not open correctly." << std::endl;
        throw EXIT_FAILURE;
    }

    LibSerial::DataBuffer dataBuffer;
    size_t BUFFER_SIZE = sizeof(WrappedPacket);

    while(true) {
        serial_port.Read(dataBuffer, sizeof(WrappedPacket));

        uint8_t* rawDataBuffer = dataBuffer.data();
        WrappedPacket wrappedPacket;

        std::memcpy(&wrappedPacket, rawDataBuffer, sizeof wrappedPacket);

        this->readFromPacket(&wrappedPacket);
        this->readFromEffectors();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

