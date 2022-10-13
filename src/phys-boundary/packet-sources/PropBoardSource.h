//
// Created by kevin on 10/12/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H

#include <libserial/SerialPort.h>
#include "PiUtils.h"
#include <mutex>
#include <thread>

class PropBoardSource {
public:
    explicit PropBoardSource(LibSerial::SerialPort port);

    PropBoardSource(const PropBoardSource& other) = delete;
    PropBoardSource(PropBoardSource&& other) noexcept ;

    PropBoardSource& operator=(const PropBoardSource& other) = delete;
    PropBoardSource& operator=(PropBoardSource&& other) = default;

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
    ~PropBoardSource() = default;


    /**
     * Provides the latest packet
     * @return packet
     */
    PropBoardSensorData getPacket();

private:
    void readFromPort();

    LibSerial::SerialPort storedPort;

    std::mutex packetMutex;
    PropBoardSensorData storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H
