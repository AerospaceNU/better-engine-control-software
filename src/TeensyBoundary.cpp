//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"

#include <utility>

TeensyBoundary::TeensyBoundary(std::string serial_port) :
        teensyPort(std::move(serial_port)),
        storedData(SensorData{}),
        m_member_thread(std::thread([this] { this->continousTeensyRead();}))
{}

SensorData TeensyBoundary::readFromBoundary() {
    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //RAII goated

    return this->storedData;
}


bool TeensyBoundary::writeToBoundary(CommandData data) {
    return false;
}


void TeensyBoundary::readFromPacket(WrappedPacket* wrappedPacket) {
    // CRC is included, but we're not checking it for validity right now

    std::lock_guard<std::mutex> lock(sensorDataWriteMutex);
    //use of RAII, that way mutex unlocks even if exceptions throw

    //dataStore->values["loxInletDucer"] = (double) wrappedPacket->dataPacket.adc4;
    storedData.loxInletDucer = wrappedPacket->dataPacket.adc4;

    //dataStore->values["kerInletDucer"] = (double) wrappedPacket->dataPacket.adc5;
    storedData.kerInletDucer = wrappedPacket->dataPacket.adc5;

    //dataStore->values["purgeDucer"] = (double) wrappedPacket->dataPacket.adc6;
    storedData.purgeDucer = wrappedPacket->dataPacket.adc6;

    //dataStore->values["kerPintleDucer"] = (double) wrappedPacket->dataPacket.adc7;
    //TODO: wtf is this

    //dataStore->values["kerTankDucer"] = (double) wrappedPacket->dataPacket.adc8;
    storedData.kerInletDucer = wrappedPacket->dataPacket.adc8;

    //dataStore->values["loxTankDucer"] = (double) wrappedPacket->dataPacket.adc9;
    storedData.loxInletDucer = wrappedPacket->dataPacket.adc9;

    //dataStore->values["pneumaticDucer"] = (double) wrappedPacket->dataPacket.adc10; //used to be pneumaticsDucer
    //TODO wtf is this

    // TODO: Determine which physical sensors these are
    //dataStore->values["loxN2Ducer"] = 0;
    //dataStore->values["kerN2Ducer"] = 0;

    // TODO: Connect these to physical sensors?
    //dataStore->values["loxVenturi"] = (double) wrappedPacket->dataPacket.adc2;
    storedData.loxVenturi = wrappedPacket->dataPacket.adc2;

    //dataStore->values["kerVenturi"] = (double) wrappedPacket->dataPacket.adc3;
    storedData.kerVenturi = wrappedPacket->dataPacket.adc3;

    // TODO: Determine which thermos are connected to which TC input (also what to do with TCs 5,6, and 7)
    //dataStore->values["manifoldInletThermo"] = filterNan(wrappedPacket->dataPacket.tc3);
    //TODO wtf is this

    //dataStore->values["manifoldOutletThermo"] = filterNan(wrappedPacket->dataPacket.tc4);
    //TODO wtf is this

    // ln2 tank
    //dataStore->values["tank1Thermo"] = filterNan(wrappedPacket->dataPacket.tc0);
    //TODO confirm this is the right tank
    storedData.loxTank1 = filterNan(wrappedPacket->dataPacket.tc0);

    // kero tank
    //dataStore->values["tank2Thermo"] = filterNan(wrappedPacket->dataPacket.tc1);
    //TODO confirm this is the right tank
    storedData.loxTank2 = filterNan(wrappedPacket->dataPacket.tc1);

    // miscalleneous
    //dataStore->values["tank3Thermo"] = filterNan(wrappedPacket->dataPacket.tc2);
    //TODO confirm this is the right tank
    storedData.loxTank3 = filterNan(wrappedPacket->dataPacket.tc2);

    //dataStore->values["loadCell"] = wrappedPacket->dataPacket.loadCell0;
    storedData.loadCell = wrappedPacket->dataPacket.loadCell0;

}

void TeensyBoundary::continousTeensyRead() {
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
        uint8_t *rawDataBuffer = dataBuffer.data();

        //this part
        auto *wrappedPacket = (WrappedPacket *) rawDataBuffer;

        this->readFromPacket((WrappedPacket *) rawDataBuffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

