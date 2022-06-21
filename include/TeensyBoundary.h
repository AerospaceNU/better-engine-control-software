//
// Created by kevin on 6/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H

#include "generic/IPhysicalBoundary.h"
#include "utils-and-constants/PiUtils.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <string>

class TeensyBoundary: public IPhysicalBoundary{
public:
    explicit TeensyBoundary(std::string serial_port);

    SensorData readFromBoundary() override;
    bool writeToBoundary(CommandData data) override;

protected:
    void continousTeensyRead();
    void readFromPacket(WrappedPacket* wrappedPacket);


    //the order of the fields here is important, so that the teensyPort is
    //intialized before the thread to avoid utter bullshit
    std::string teensyPort;

    SensorData storedData;

    std::mutex sensorDataWriteMutex;
    std::thread m_member_thread;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
