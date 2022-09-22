//
// Created by kevin on 9/20/2022.
//

#include "ADCPacketSource.h"
#include <cstring>

ADCPacketSource::ADCPacketSource(LibSerial::SerialPort port):
    storedPort(std::move(port)),
    //TODO: get some zero constructor for the packets
    updatingThread([this]() {
        while(true){
            this->readFromPort();
        }
    })

// if we ever get to use C++20, replace the above def with this
//    updatingThread([this](std::stop_token token) {
//        while(token.stop_requested()) {
//            this->readPackets();
//        }
//    })
{}

ADCPacketSource::ADCPacketSource(ADCPacketSource&& other):
        storedPort(std::move(other.storedPort)),
        packetMutex(),
        storedData(std::move(other.storedData)),
        updatingThread(std::move(other.updatingThread))
{}

AdcBreakoutSensorData ADCPacketSource::getPacket() {
    std::lock_guard<std::mutex> lock(packetMutex);
    return storedData;
}


void ADCPacketSource::readFromPort() {
    LibSerial::DataBuffer dataBuffer;
    this->storedPort.Read(dataBuffer, sizeof(AdcBreakoutSensorData));
    uint8_t *rawDataBuffer = dataBuffer.data();
    //TODO: implement CRC checking


    AdcBreakoutSensorData aPacket;
    std::memcpy(&aPacket, rawDataBuffer, sizeof aPacket);

    std::lock_guard<std::mutex> lock(packetMutex);
    storedData = aPacket;
}