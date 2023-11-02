//
// Created by kevin on 6/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H

#include "IPhysicalBoundary.h"

#include "valves/IECSValve.h"

#include "packet-sources/IPacketSource.h"
#include "phys-boundary/packet-sources/PiUtils.h"

#include "calibrators/SensorDataCalibrator.h"

#include <vector>
#include <etl/vector.h>
#include <memory>

/**
 * Implementation of IPhysicalBoundary for getting and sending data to horizontal
 * test stand.
 *
 * Sensor readings are passed to this IPhysicalBoundary by the Teensy Arduino and other boards,
 * requiring us to read data from a serial port. Effector readings and commands are handled
 * directly.
 */
class TeensyBoundary: public IPhysicalBoundary{
public:
    explicit TeensyBoundary(std::unique_ptr<IECSValve> loxPressurant,
                            std::unique_ptr<IECSValve> kerPressurant,
                            std::unique_ptr<IECSValve> loxPurge,
                            std::unique_ptr<IECSValve> kerPurge,
                            std::unique_ptr<IECSValve> loxVent,
                            std::unique_ptr<IECSValve> kerVent,
                            std::unique_ptr<IECSValve> loxFlow,
                            std::unique_ptr<IECSValve> kerFlow,
                            std::unique_ptr<IECSValve> kerOrifice,
                            std::unique_ptr<IECSValve> loxDrip,
                            std::unique_ptr<IECSValve> kerDrip,

                            std::unique_ptr<IPacketSource<PropBoardSensorData>> packetSource,
                            etl::vector<SensorDataCalibrator, 30> calibratorList = {});


    TeensyBoundary(const TeensyBoundary& other) = delete;
    TeensyBoundary(TeensyBoundary&& other) = default;

    TeensyBoundary& operator=(const TeensyBoundary& other) = delete;
    TeensyBoundary& operator=(TeensyBoundary&& other) = default;

    ~TeensyBoundary() override = default;

    /**
     * Returns the latest stored sensor data.
     * Reads the latest info from the packet sources and effectors
     *
     * Mutates stored field
     *
     * @return a new SensorData object
     */
    SensorData readFromBoundary() override;
    void writeToBoundary(const CommandData& data) override;

private:
    /**
     * Updates the storedState parameter with newest data from effectors
     * Effectors are read directly, not through data packet transmission
     */
    void readFromEffectors(SensorData& storedData);

    std::unique_ptr<IECSValve> loxPressurant;
    std::unique_ptr<IECSValve> kerPressurant;
    std::unique_ptr<IECSValve> loxPurge;
    std::unique_ptr<IECSValve> kerPurge;
    std::unique_ptr<IECSValve> loxVent;
    std::unique_ptr<IECSValve> kerVent;
    std::unique_ptr<IECSValve> loxFlow;
    std::unique_ptr<IECSValve> kerFlow;
    std::unique_ptr<IECSValve> kerOrifice;
    std::unique_ptr<IECSValve> loxDrip;
    std::unique_ptr<IECSValve> kerDrip;

    std::unique_ptr<IPacketSource<PropBoardSensorData>> packetSource;

    etl::vector<SensorDataCalibrator, 30> calibratorList;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
