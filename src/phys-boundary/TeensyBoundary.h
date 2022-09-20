//
// Created by kevin on 6/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H

#include "IPhysicalBoundary.h"

#include "valves/IECSValve.h"
#include "packet-sources/ADCPacketSource.h"
#include "packet-sources/TeensyPacketSource.h"
#include "calibrators/SensorDataCalibrator.h"

#include "PiUtils.h"
#include <mutex>
#include <thread>
#include <string>
#include <vector>
#include <libserial/SerialPort.h>

/**
 * Implementation of IPhysicalBoundary for getting and sending data to horizontal
 * test stand.
 *
 * Sensor readings are passed to this IPhysicalBoundary by the Teensy Arduino and other boards,
 * requiring us to read data from a serial port. Effector readings and commands are handled
 * directly.
 */
 /*
  * TODO: discuss plans for testing objects with the team
  *
  * As it stands right now, testing this object is either impossible
  * or ridiculously dumb thanks to it taking in LibSerial::SerialPort
  *
  * For starters LibSerial is only for Linux, which is a problem for everyone else
  *
  * Just ratting some ideas out, we could
  *
  * 1.) make a new interface like ISerialPort, make a wrapper class around
  * LibSerial::SerialPort that implements it
  *     - that way we could inject a fake ISerialPort for tests
  *
  * 2.) if we decide to go message passing with a thread-safe queue approach,
  * we can encapsulate the idea of passing structs to the queue with other interface,
  * and then have a method like void feedToQueue(ThreadQueue& queue). Then we could
  * once again make a wrapper object for LibSerial::SerialPort that implements it
  *
  * 3.) another alternative if we do message passing, we can make an interface like
  * IPacketSource<T>, so it's generic for each packet, and have a method like
  * T getPacket().
  */
class TeensyBoundary: public IPhysicalBoundary{
public:
    TeensyBoundary(ADCPacketSource adcSrc,
                   TeensyPacketSource tSrc,
                   std::vector<SensorDataCalibrator> calibratorList = {});

    /*
     * std::mutex is not copyable or movable
     *
     * Because of this, it's probably better to explicitly delete
     * the copy/move constructor, as well as the general assignment
     * constructor
     */
    TeensyBoundary(const TeensyBoundary& other) = delete;
    TeensyBoundary(TeensyBoundary&& other) = delete;

    TeensyBoundary& operator=(TeensyBoundary other) = delete;

    /**
     * Destructor for boundary
     *
     * Not subtle why the default constructor is good enough
     *
     * The worker thread has to be destroyed when the object is destroyed, otherwise bad times will happen with
     * accessing deallocated memory.
     * In addition, std::thread will freak out and call std::terminate if it is destructed before joining it. So,
     * we have to have a way to signal to our thread to stop so we can join it
     *
     * //TODO
     * Currently, we cannot use std::jthread due to not being on C++20. We could do the below manually,
     * but considering that the destructor is only really called once at the very end of the program, we
     * can probably be lazy and leave it, or just apply the easy jthread fix if we get on C++20
     *
     * Because of this, THE BELOW IS CURRENTLY NOT RELEVANT
     *
     *
     * workerThread is a std::jthread, not a std::thread. jthreads allow us to request
     * for the thread to stop (this stop token can be seen in the constructor),
     * through the request_stop() method. The default destructor for std::jthread
     * will call request_stop() itself if the thread isn't detached, so the cleanup
     * we need is already default
     *
     * Note this means that the choice to use std::jthread over std::thread is critical
     */
    ~TeensyBoundary() override = default;


    /**
     * Returns the latest stored sensor data.
     * Locks the sensor data mutex to avoid data races.
     * @return a SensorData object
     */
    SensorData readFromBoundary() override;
    void writeToBoundary(CommandData& data) override;

private:
    /**
     * Updates the storedState field with newest data from effectors
     * Effectors are read directly, not through data packet transmission
     *
     * NOTE: DOES NOT LOCK ANY MUTEXES, MUST BE DONE OUTSIDE OF THIS METHOD
     */
    void readFromEffectors();

    /*
     * TODO: reconsider the use of threads
     *
     * at this point we have 2 mutexes in our object. while one is alright, I think two is risky and
     * certainly anything over that we should seriously take a look at
     *
     * Matt from avionics suggested we could just read packets directly in the readFromBoundary method
     * The issue I'm thinking of is that if the packet never comes, readFromBoundary will hang foreve,
     * so the rest of the program will probably also hang forever
     *
     * We could probably try some timeouts, but once again this deserves some thought
     *
     * Or alternatively, we could keep threads and just use message passing with
     * a thread-safe queue
     */

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

    std::vector<SensorDataCalibrator> calibratorList;

    SensorData storedData;

    ADCPacketSource adcSource;
    TeensyPacketSource teensySource;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_TEENSYBOUNDARY_H
