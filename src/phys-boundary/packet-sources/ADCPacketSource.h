//
// Created by kevin on 9/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
#include <libserial/SerialPort.h>
#include "../PiUtils.h"
#include <mutex>
#include <thread>

/**
 * Class that supplies data packets from ADC breakout board.
 *
 * In the background, it contains a thread that is continuously reading
 * from the serial port.
 */
class ADCPacketSource {
public:
    explicit ADCPacketSource(LibSerial::SerialPort port);

    ADCPacketSource(const ADCPacketSource& other) = delete;
    ADCPacketSource(ADCPacketSource&& other);

    ADCPacketSource& operator=(const ADCPacketSource& other) = delete;
    ADCPacketSource& operator=(ADCPacketSource&& other) = default;

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
     * updatingThread is a std::jthread, not a std::thread. jthreads allow us to request
     * for the thread to stop (this stop token can be seen in the constructor),
     * through the request_stop() method. The default destructor for std::jthread
     * will call request_stop() itself if the thread isn't detached, so the cleanup
     * we need is already default
     *
     * Note this means that the choice to use std::jthread over std::thread is critical
     */
    ~ADCPacketSource() = default;

    /**
     * Provides the latest packet
     * @return packet
     */
    AdcBreakoutSensorData getPacket();

private:
    void readFromPort();

    LibSerial::SerialPort storedPort;

    std::mutex packetMutex;
    AdcBreakoutSensorData storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
