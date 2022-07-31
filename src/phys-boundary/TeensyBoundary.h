//
// Created by kevin on 6/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H

#include "IPhysicalBoundary.h"

#include "phys-boundary/valves/IECSValve.h"
#include "PiUtils.h"

#include <mutex>
#include <thread>
#include <string>

/**
 * Implementation of IPhysicalBoundary for getting and sending data to horizontal
 * test stand.
 *
 * Sensor readings are passed to this CommBoundary by the Teensy Arduino, requiring
 * us to read data from a serial port. Effector readings and commands are handled
 * directly in this CommBoundary.
 */
class TeensyBoundary: public IPhysicalBoundary{
public:
    TeensyBoundary(std::string adcboardPortLoc, std::string teensyPortLoc);

    /**
     * Returns the latest stored sensor data.
     * Locks the sensor data mutex to avoid data races.
     * @return a SensorData object
     */
    SensorData readFromBoundary() override;
    void writeToBoundary(CommandData& data) override;

protected:
    /**
     * Continuously reads sensor data from Teensy's serial port, as well
     * as raw from the actual valves and shit. To be ran in a separate thread.
     */
    void continuousSensorRead(std::string adcboardPortLoc, std::string teensyPortLoc);

    /**
     * Updates the storedState field for load cell and TC data packet
     * Locks the sensor data mutex to avoid data races
     * @param wrappedPacket reference to data packet from serial packet
     */
    void readFromTeensy(WrappedPacket& wrappedPacket);

    /**
     * Updates the storedState field to pressurant data from packet
     * Locks the sensor data mutex to avoid data races
     * @param adcPacket reference to data packet from serial packet
     */
    void readFromADCBoard(AdcBreakoutSensorData& adcPacket);

    /**
     * Updates the storedState field with newest data from effectors
     * Effectors are read directly, not through data packet transmission
     * Locks the sensor data mutex to avoid data races
     */
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

    SensorData storedData;
    /**
     * This mutex MUST be locked before trying to read or write to the storedData field for
     * thread safety. Otherwise a data race could occur
     */
    std::mutex sensorDataWriteMutex;

    std::thread workerThread;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
