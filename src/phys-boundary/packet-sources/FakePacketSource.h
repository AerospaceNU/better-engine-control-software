//
// Created by David.L on 10/24/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEPACKETSOURCE_H
#include "IPacketSource.h"

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

