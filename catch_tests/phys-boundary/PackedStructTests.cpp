//
// Created by kevin on 11/7/2022.
//

#include "../catch.hpp"
#include "phys-boundary/packet-sources/PiUtils.h"
#include <atomic>

TEST_CASE("std::atomic on packed struct", "[unit]"){
    PropBoardSensorData data{};
    REQUIRE(data.adc10 == 0);
    data.adc10 = 5;
    REQUIRE(data.adc10 == 5);

    std::atomic<PropBoardSensorData> atomicData{data};
    auto newData = atomicData.load();
    REQUIRE(newData.adc10 == 5);

    std::atomic<PropBoardSensorData> defaultAtom{PropBoardSensorData{}};
    auto newData2 = defaultAtom.load();
    REQUIRE(newData2.adc10 == 0);
}