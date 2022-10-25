//
// Created by David.L on 10/24/22.
//



#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIPACKETSOURCE_H
#include "IPacketSource.h"

template<typename T>
class FakeIPacketSource : public IPacketSource<T> {
public:
    explicit FakeIPacketSource(T data) {
        {
            storedData = data;
        }
    }

    T getPacket() override {
        return storedData;
    }
private:
    T storedData;

}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIPACKETSOURCE_H

