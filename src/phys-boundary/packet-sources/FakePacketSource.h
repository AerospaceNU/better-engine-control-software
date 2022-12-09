//
// Created by David.L on 10/24/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEPACKETSOURCE_H
#include "IPacketSource.h"

/**
 * Basic impl of an IPacketSource that takes in what
 * data to output in constructor, and spits out the same
 * in the getPacket method
 *
 * Useful for unit testing
 * @tparam T type of data packet we want
 */
template<typename T>
class FakePacketSource : public IPacketSource<T> {
public:
    explicit FakePacketSource(T data) {
        {
            storedData = data;
        }
    }

    T getPacket() override {
        return storedData;
    }
private:
    T storedData;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEPACKETSOURCE_H

