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

/**
 * Implementation of IPhysicalBoundary for getting and sending data to Teensy Arduino
 * on test stand
 */
class TeensyBoundary: public IPhysicalBoundary{
public:
    explicit TeensyBoundary(std::string serial_port);

    /**
     * Returns the latest stored sensor data.
     * Locks the sensor data mutex to avoid data races.
     * @return a SensorData object
     */
    SensorData readFromBoundary() override;
    bool writeToBoundary(CommandData data) override;

protected:
    /**
     * Continuously reads sensor data from Teensy's serial port. To be
     * ran in a separate thread.
     */
    void continousTeensyRead();

    /**
     * Updates the storedState field to newest data from serial port
     * Locks the sensor data mutex to avoid data races
     * @param wrappedPacket
     */
    void readFromPacket(WrappedPacket* wrappedPacket);


    //the order of the fields here is important, so that the teensyPort is
    //intialized before the thread to avoid utter bullshit
    std::string teensyPort;

    SensorData storedData;

    std::mutex sensorDataWriteMutex;
    std::thread m_member_thread;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
