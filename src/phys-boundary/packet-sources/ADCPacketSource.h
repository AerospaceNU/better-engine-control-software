//
// Created by kevin on 9/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
#include <libserial/SerialPort.h>
#include "../PiUtils.h"
#include <mutex>
#include <thread>

class ADCPacketSource {
public:
    ADCPacketSource(LibSerial::SerialPort port);

    ADCPacketSource(const ADCPacketSource& other) = delete;
    ADCPacketSource(ADCPacketSource&& other);

    ADCPacketSource& operator=(const ADCPacketSource& other) = delete;
    ADCPacketSource& operator=(ADCPacketSource&& other) = default;

    //meh
    ~ADCPacketSource() = default;

    AdcBreakoutSensorData getPacket();

private:
    void readFromPort();

    LibSerial::SerialPort storedPort;

    std::mutex packetMutex;
    AdcBreakoutSensorData storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
