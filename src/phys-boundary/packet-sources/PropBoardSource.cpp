//
// Created by kevin on 10/12/2022.
//

#include "PropBoardSource.h"
#include <utility>

PropBoardSource::PropBoardSource(LibSerial::SerialPort port):
    //TODO: init stored data to all 0
    storedPort(std::move(port)),
    updatingThread([this]() {
        while(true){
            this->readFromPort();
        }
    })
{}

// if we ever get to use C++20, replace the above def with this
//    updatingThread([this](std::stop_token token) {
//        while(token.stop_requested()) {
//            this->readPackets();
//        }
//    })

PropBoardSource::PropBoardSource(PropBoardSource&& other):
        storedPort(std::move(other.storedPort)),
        packetMutex(),
        storedData(other.storedData),
        updatingThread(std::move(other.updatingThread))
{}

PropBoardSensorData PropBoardSource::getPacket() {
    std::lock_guard<std::mutex> lock(packetMutex);
    return storedData;
}

void PropBoardSource::readFromPort() {
    LibSerial::DataBuffer dataBuffer;
    this->storedPort.Read(dataBuffer, sizeof(PropBoardSensorData));
    uint8_t *rawDataBuffer = dataBuffer.data();
    //TODO: implement CRC checking


    PropBoardSensorData aPacket;
    std::memcpy(&aPacket, rawDataBuffer, sizeof aPacket);

    {
        std::lock_guard<std::mutex> lock(packetMutex);
        this->storedData = aPacket;
    }
}