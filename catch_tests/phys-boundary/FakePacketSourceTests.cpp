//
// Created by kevin on 12/11/2022.
//

#include "../catch.hpp"
#include "phys-boundary/packet-sources/FakePacketSource.h"

TEST_CASE("FakePacketSource tests", "[unit]"){
    FakePacketSource<int> src{1243};

    REQUIRE(src.getPacket() == 1243);
}