//
// Created by kevin on 10/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
#include "IPacketSource.h"

#include <libserial/SerialPort.h>
#include "PiUtils.h"

#include <atomic>
#include <thread>
#include <utility>
#include <cstring>
#include <iostream>

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
class SerialPortSource : public IPacketSource<T>
{
public:
    explicit SerialPortSource(LibSerial::SerialPort port, bool (*verifiFunct)(const WrappedPacket<T> &)) : storedPort(std::move(port)),
                                                                                                           verificationFunct(std::move(verifiFunct)),
                                                                                                           storedData(T{}),
                                                                                                           updatingThread([this](std::stop_token token)
                                                                                                                          {
            while(not token.stop_requested()) {
                this->readFromPort();
            } })
    {
    }

    SerialPortSource(const SerialPortSource &other) = delete;

    SerialPortSource(SerialPortSource &&other) = delete;

    SerialPortSource &operator=(const SerialPortSource &other) = delete;

    SerialPortSource &operator=(SerialPortSource &&other) = delete;

    /**
     * Destructor for boundary
     *
     * Not subtle why the default constructor is good enough
     *
     * The worker thread has to be destroyed when the object is destroyed, otherwise bad times will happen with it
     * accessing deallocated memory.
     * A std::thread would freak out and call std::terminate if it is destructed before joining it. So,
     * we have to have a way to signal to our thread to stop so we can join it
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
    T getPacket() override
    {
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
    void readFromPort()
    {
        WrappedPacket<T> packet;

        LibSerial::DataBuffer dataBuffer;
        this->storedPort.Read(dataBuffer, sizeof packet);

        // avoid strict aliasing for this type pun
        std::memcpy(&packet, dataBuffer.data(), sizeof packet);

        if (this->verificationFunct(packet) == true)
        {
            this->storedData.store(packet.dataPacket);
        }
        else
        {
            std::cout << "Bad packet, flushing\n";
            // reset contents of buffer, in case desynced read
            this->storedPort.FlushInputBuffer();
        }
    }

    LibSerial::SerialPort storedPort;

    bool (*verificationFunct)(const WrappedPacket<T> &);
    std::atomic<T> storedData;

    std::jthread updatingThread;
};

#endif // BETTER_ENGINE_CONTROL_SOFTWARE_SERIALPORTSOURCE_H
