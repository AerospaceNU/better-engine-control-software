//
// Created by kevin on 9/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYPACKETSOURCE_H
#include <libserial/SerialPort.h>
#include "../PiUtils.h"
#include <mutex>
#include <thread>

class TeensyPacketSource {
public:
    TeensyPacketSource(LibSerial::SerialPort port);

    TeensyPacketSource(const TeensyPacketSource& other) = delete;
    TeensyPacketSource(TeensyPacketSource&& other) = default;

    TeensyPacketSource& operator=(const TeensyPacketSource& other) = delete;
    TeensyPacketSource& operator=(TeensyPacketSource&& other) = default;

    //meh
    ~TeensyPacketSource() = default;

    TeensyData getPacket();

private:
    void readFromPort();

    LibSerial::SerialPort storedPort;

    std::mutex packetMutex;
    TeensyData storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYPACKETSOURCE_H
