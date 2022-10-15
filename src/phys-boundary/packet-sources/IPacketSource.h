//
// Created by kevin on 10/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H

template<typename T>
class IPacketSource{
public:
    virtual T getPacket() = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H
