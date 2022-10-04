//
// Created by kevin on 9/20/2022.
//

#include "TeensyPacketSource.h"
#include <cstring>

TeensyPacketSource::TeensyPacketSource(LibSerial::SerialPort port):
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

TeensyPacketSource::TeensyPacketSource(TeensyPacketSource&& other):
    storedPort(std::move(other.storedPort)),
    packetMutex(),
    storedData(std::move(other.storedData)),
    updatingThread(std::move(other.updatingThread))
{}


TeensyData TeensyPacketSource::getPacket() {
    std::lock_guard<std::mutex> lock(packetMutex);
    return storedData;
}


void TeensyPacketSource::readFromPort() {
    LibSerial::DataBuffer dataBuffer;
    this->storedPort.Read(dataBuffer, sizeof(WrappedPacket));
    uint8_t *rawDataBuffer = dataBuffer.data();
    //TODO: implement CRC checking


    WrappedPacket wPacket;
    std::memcpy(&wPacket, rawDataBuffer, sizeof wPacket);

    {
        std::lock_guard<std::mutex> lock(packetMutex);
        this->storedData = wPacket.dataPacket;
    }
}
