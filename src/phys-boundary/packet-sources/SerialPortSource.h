//
// Created by kevin on 10/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#include "IPacketSource.h"

#include <libserial/SerialPort.h>
#include "PiUtils.h"
#include <mutex>
#include <thread>

#include <utility>
#include <cstring>

template <typename T>
class SerialPortSource: public IPacketSource<T> {
public:
    explicit SerialPortSource(LibSerial::SerialPort port){
        //TODO: init stored data to all 0
        storedPort(std::move(port)),
        updatingThread([this]() {
            while(true){
                this->readFromPort();
            }
        })
    }
    // if we ever get to use C++20, replace the above def with this
//    updatingThread([this](std::stop_token token) {
//        while(token.stop_requested()) {
//            this->readPackets();
//        }
//    })


    SerialPortSource(const SerialPortSource& other) = delete;

    SerialPortSource(SerialPortSource&& other) noexcept:
            storedPort(std::move(other.storedPort)),
            packetMutex(),
            storedData(other.storedData),
            updatingThread(std::move(other.updatingThread))
    {}

    SerialPortSource& operator=(const SerialPortSource& other) = delete;

    SerialPortSource& operator=(SerialPortSource&& other) = default;

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
    ~SerialPortSource() = default;


    /**
     * Provides the latest packet
     * @return packet
     */
    T getPacket() override {
        {
            std::lock_guard<std::mutex> lock(packetMutex);
            return storedData;
        }
    }

private:
    void readFromPort() {
        LibSerial::DataBuffer dataBuffer;
        this->storedPort.Read(dataBuffer, sizeof(T));
        uint8_t *rawDataBuffer = dataBuffer.data();
        //TODO: implement CRC checking


        T packet;
        std::memcpy(&packet, rawDataBuffer, sizeof packet);

        {
            std::lock_guard<std::mutex> lock(packetMutex);
            this->storedData = packet;
        }
    }

    LibSerial::SerialPort storedPort;

    std::mutex packetMutex;
    T storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
