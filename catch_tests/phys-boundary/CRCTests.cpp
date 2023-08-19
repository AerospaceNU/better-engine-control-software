//
// Created by allison on 11/30/2022.
//

#include "../catch.hpp"
#include "phys-boundary/packet-sources/CrcChecking.h"
#include <cstring>


namespace {
    struct TestPacket {
        // I want this struct to be packed across all platforms, except I really don't wanna
        // added compiler specific packing pragmas just for this. Hopefully the compilers wwe
        // use are sane and pack 4 8-bit contiguous data members into 4 side by side bytes with
        // no padding, but that might not be the case.
        uint8_t dataMembers[4];
    };

    // TODO: this is a compile-time check on the TestPacket. Might be worth trying to figure out how
    // to disable the unit test if the assertion is false, instead of failing the build entirely
    static_assert(sizeof(TestPacket) == 4);
}

TEST_CASE("CRC", "[unit]"){
    SECTION("On zero-ed packet") {    
        WrappedPacket<TestPacket> zeroedPacket;
        std::memset(&zeroedPacket.dataPacket, 0 , sizeof zeroedPacket.dataPacket);

        SECTION("With correct crc field") {
            zeroedPacket.packetCRC = 0;
            REQUIRE(checkCrc(zeroedPacket));
        }

        SECTION("With incorrect crc field") {
            zeroedPacket.packetCRC = 432;
            REQUIRE_FALSE(checkCrc(zeroedPacket));
        }
    }

    SECTION("On non-zeroed packet") {
        WrappedPacket<TestPacket> packet;
        packet.dataPacket.dataMembers[0] = 1;
        packet.dataPacket.dataMembers[1] = 2;
        packet.dataPacket.dataMembers[2] = 3;
        packet.dataPacket.dataMembers[3] = 4;

        SECTION("With correct crc field") {
            packet.packetCRC = 3331;
            REQUIRE(checkCrc(packet));
        }

        SECTION("With incorrect crc field") {
            packet.packetCRC = 432;
            REQUIRE_FALSE(checkCrc(packet));
        }
    }
}
