#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_CRCTESTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_CRCTESTS_H

#include "PiUtils.h"
#include <CRC16.h>

#include <cstring>

/**
 * Checks if the contents of the inner packet matches the CRC field in WrappedPacket
 * We assume that packet is packed, aka there are no padding bytes in it that might screw up the computation
 * Returns true if match, false if not
*/template <typename T>
bool checkCrc(const WrappedPacket<T>& packet){
    uint8_t rawDataBuffer[sizeof packet];

    // avoid strict aliasing for this type pun
    // a raw C-style cast is technically UB (becomes more obvious if you try a static_cast)
    //
    // NOTE: I wanted to use std::bit_cast which is more readable. The issue is that it needs to 
    // return a uint8_t[N] array. And thanks to C's GREAT array decay mechanism, that doesn't work.
    // A possible solution is to just use std::array which supports value semantics and access the data 
    // pointer but fuck that that sounds worse then the current memcpy
    static_assert(sizeof packet == sizeof rawDataBuffer);
    std::memcpy(&rawDataBuffer, &packet, sizeof rawDataBuffer);

    CRC16 crc;
    crc.restart();
    crc.add(rawDataBuffer, sizeof(packet.dataPacket));
    uint16_t calculated_crc = crc.getCRC();
    
    return calculated_crc == packet.packetCRC;
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_CRCTESTS_H
