//
// Created by kevin on 10/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H

/**
 * A general abstraction that represents something
 * we can get data from
 * @tparam T type of data packet we want
 */
template<typename T>
class IPacketSource{
public:
    virtual T getPacket() = 0;

    virtual ~IPacketSource() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IPACKETSOURCE_H