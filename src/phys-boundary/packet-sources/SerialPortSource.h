//
// Created by kevin on 10/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#include "IPacketSource.h"

#include <libserial/SerialPort.h>
#include "PiUtils.h"
#include <functional>

#include <atomic>
#include <thread>
#include <utility>
#include <cstring>

/**
 * Generic implementation of IPacketSource using data from LibSerial ports
 * IMPORTANT: Internally, this object reads a WrappedPacket<T> from the port,
 * not just a raw T. A WrappedPacket includes a CRC field, so the actual size of the
 * object read is 2+ more bytes than the size of T
 *
 * Performs CRC checking, additional checking (ex. filtering NaNs from doubles)
 * may have to be done outside
 *
 * @tparam T packet type to gather and return
 */
template <typename T>
class SerialPortSource: public IPacketSource<T> {
public:
    explicit SerialPortSource(LibSerial::SerialPort port, std::function<bool(const WrappedPacket<T>&)> verifiFunct):
        storedPort(std::move(port)),
        verificationFunct(std::move(verifiFunct)),
        storedData(T{}),
        updatingThread([this]() {
            while(true){
                this->readFromPort();
            }
        })
    {}
    // if we ever get to use C++20, replace the above def with this
//    updatingThread([this](std::stop_token token) {
//        while(token.stop_requested()) {
//            this->readPackets();
//        }
//    })


    SerialPortSource(const SerialPortSource& other) = delete;

    SerialPortSource(SerialPortSource&& other) = delete;

    SerialPortSource& operator=(const SerialPortSource& other) = delete;

    SerialPortSource& operator=(SerialPortSource&& other) = delete;

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
        return storedData.load();
    }

private:
    /**
     * Gets data from serial port, interprets as a WrappedPacket<T>, and finally verifies that the data
     * has not been corrupted during the transfer (this is likely CRC checking)
     *
     * If the verification succeeds, updates the stored data thread-safely
     *
     * Else, disposes of the data and flushes the upcoming data buffer in case of a desync     *
     */
    void readFromPort() {
        LibSerial::DataBuffer dataBuffer;
        this->storedPort.Read(dataBuffer, sizeof(WrappedPacket<T>));
        uint8_t *rawDataBuffer = dataBuffer.data();

        WrappedPacket<T> packet;
        std::memcpy(&packet, rawDataBuffer, sizeof(WrappedPacket<T>));

        //TODO: implement CRC checking on WrappedPacket
        if (this->verificationFunct(packet) == true)
        {
            this->storedData.store(packet.dataPacket);
        }
        else{
            //reset contents of buffer, in case desynced read
            this->storedPort.FlushInputBuffer();
        }
    }

    LibSerial::SerialPort storedPort;

    std::function<bool(const WrappedPacket<T>&)> verificationFunct;
    std::atomic<T> storedData;

    std::thread updatingThread;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
