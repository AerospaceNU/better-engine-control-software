//
// Created by kevin on 10/17/2022.
//

#include "../catch.hpp"
#include "utils/SensorDataUtils.h"

TEST_CASE("SensorData average", "[unit]"){
    SensorData data1;
    SensorData data2;
    data1.loxVent = ECSValveState::OPEN;
    data1.kerVent = ECSValveState::OPEN;
    data1.loxDrip = ECSValveState::OPEN;
    data1.kerDrip = ECSValveState::OPEN;
    data1.loxPressurant = ECSValveState::OPEN;
    data1.kerPressurant = ECSValveState::OPEN;
    data1.loxFlow = ECSValveState::OPEN;
    data1.kerFlow  = ECSValveState::OPEN;
    data1.loxPurge = ECSValveState::OPEN;
    data1.kerPurge = ECSValveState::OPEN;
    data1.loxTankDucer = 5;
    data1.kerTankDucer = 5;
    data1.purgeDucer = 5;
    data1.loxInletDucer = 5;
    data1.kerInletDucer = 5;
    data1.kerPintleDucer = 5;
    data1.loxVenturi = 5;
    data1.kerVenturi = 5;
    data1.pnematicsDucer = 5;
    data1.loadCell = 5;

    data2.loxVent = ECSValveState::CLOSED;
    data2.kerVent = ECSValveState::CLOSED;
    data2.loxDrip = ECSValveState::CLOSED;
    data2.kerDrip = ECSValveState::CLOSED;
    data2.loxPressurant = ECSValveState::CLOSED;
    data2.kerPressurant = ECSValveState::CLOSED;
    data2.loxFlow = ECSValveState::CLOSED;
    data2.kerFlow  = ECSValveState::CLOSED;
    data2.loxPurge = ECSValveState::CLOSED;
    data2.kerPurge = ECSValveState::CLOSED;
    data2.loxTankDucer = 10;
    data2.kerTankDucer = 10;
    data2.purgeDucer = 10;
    data2.loxInletDucer = 10;
    data2.kerInletDucer = 10;
    data2.kerPintleDucer = 10;
    data2.loxVenturi = 10;
    data2.kerVenturi = 10;
    data2.pnematicsDucer = 10;
    data2.loadCell = 10;
    std::vector<SensorData> input = {data1, data2};

    SensorData result = averageData(input);

    REQUIRE(result.loxVent == ECSValveState::CLOSED);
    REQUIRE(result.kerVent == ECSValveState::CLOSED);
    REQUIRE(result.loxDrip == ECSValveState::CLOSED);
    REQUIRE(result.kerDrip == ECSValveState::CLOSED);
    REQUIRE(result.loxPressurant == ECSValveState::CLOSED);
    REQUIRE(result.kerPressurant == ECSValveState::CLOSED);
    REQUIRE(result.loxFlow == ECSValveState::CLOSED);
    REQUIRE(result.kerFlow == ECSValveState::CLOSED);
    REQUIRE(result.loxPurge == ECSValveState::CLOSED);
    REQUIRE(result.kerPurge == ECSValveState::CLOSED);
    REQUIRE(result.loxTankDucer == 8);
    REQUIRE(result.kerTankDucer == 8);
    REQUIRE(result.purgeDucer == 8);
    REQUIRE(result.loxInletDucer == 8);
    REQUIRE(result.kerInletDucer == 8);
    REQUIRE(result.kerPintleDucer == 8);
    REQUIRE(result.loxVenturi == 8);
    REQUIRE(result.kerVenturi == 8);
    REQUIRE(result.pnematicsDucer == 8);
    REQUIRE(result.loadCell == 8);

    std::vector<SensorData> empty_input;

    SensorData empty = averageData(empty_input);

    REQUIRE(empty.loxVent == ECSValveState::INVALID);
    REQUIRE(empty.kerVent == ECSValveState::INVALID);
    REQUIRE(empty.loxDrip == ECSValveState::INVALID);
    REQUIRE(empty.kerDrip == ECSValveState::INVALID);
    REQUIRE(empty.loxPressurant == ECSValveState::INVALID);
    REQUIRE(empty.kerPressurant == ECSValveState::INVALID);
    REQUIRE(empty.loxFlow == ECSValveState::INVALID);
    REQUIRE(empty.kerFlow == ECSValveState::INVALID);
    REQUIRE(empty.loxPurge == ECSValveState::INVALID);
    REQUIRE(empty.kerPurge == ECSValveState::INVALID);
    REQUIRE(empty.loxTankDucer == 0);
    REQUIRE(empty.kerTankDucer == 0);
    REQUIRE(empty.purgeDucer == 0);
    REQUIRE(empty.loxInletDucer == 0);
    REQUIRE(empty.kerInletDucer == 0);
    REQUIRE(empty.kerPintleDucer == 0);
    REQUIRE(empty.loxVenturi == 0);
    REQUIRE(empty.kerVenturi == 0);
    REQUIRE(empty.pnematicsDucer == 0);
    REQUIRE(empty.loadCell == 0);
}