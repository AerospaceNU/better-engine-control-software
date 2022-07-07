//
// Created by kevin on 6/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H

#include "IPhysicalBoundary.h"
#include "utils-and-constants/PiUtils.h"
#include "phys boundary/valves/IECSValve.h"
#include "phys boundary/valves/ECSPiValve.h"
#include "phys boundary/valves/ECSThreeWayPiValve.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <string>

/**
 * Implementation of IPhysicalBoundary for getting and sending data to horizontal
 * test stand.
 *
 * Sensor readings are passed to this boundary by the Teensy Arduino, requiring
 * us to read data from a serial port. Effector readings and commands are handled
 * directly in this boundary.
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
    void writeToBoundary(CommandData data) override;

protected:
    /**
     * Continuously reads sensor data from Teensy's serial port, as well
     * as raw from the actual valves and shit. To be ran in a separate thread.
     */
    void continuousSensorRead();

    /**
     * Updates the storedState field to newest data from serial port
     * Locks the sensor data mutex to avoid data races
     * @param wrappedPacket
     */
    void readFromPacket(WrappedPacket* wrappedPacket);

    void readFromEffectors();

    IECSValve* loxPressurant;
    IECSValve* kerPressurant;
    IECSValve* loxPurge;
    IECSValve* kerPurge;
    IECSValve* loxVent;
    IECSValve* kerVent;
    IECSValve* loxFlow;
    IECSValve* kerFlow;
    IECSValve* loxDrip;
    IECSValve* kerDrip;

    //the order of the fields here is important, so that the teensyPort is
    //intialized before the thread to avoid utter bullshit
    std::string teensyPort;

    SensorData storedData;

    std::mutex sensorDataWriteMutex;
    std::thread m_member_thread;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
