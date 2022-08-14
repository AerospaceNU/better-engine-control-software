//
// Created by kevin on 8/14/2022.
//

#include "../catch.hpp"
#include "utils-and-constants/SensorData.h"

TEST_CASE("Default constructor of SensorData", "[bruh]"){
    SensorData data;

    REQUIRE(data.loxVent == ECSValveState::INVALID);
    REQUIRE(data.loxVent == ECSValveState::INVALID);
    REQUIRE(data.kerVent == ECSValveState::INVALID);
    REQUIRE(data.loxDrip == ECSValveState::INVALID);
    REQUIRE(data.kerDrip == ECSValveState::INVALID);
    REQUIRE(data.loxPressurant == ECSValveState::INVALID);
    REQUIRE(data.kerPressurant == ECSValveState::INVALID);
    REQUIRE(data.loxFlow == ECSValveState::INVALID);
    REQUIRE(data.kerFlow == ECSValveState::INVALID);
    REQUIRE(data.loxPurge == ECSValveState::INVALID);
    REQUIRE(data.kerPurge == ECSValveState::INVALID);

    //PRESSURE SENSORS (psi)
    REQUIRE(data.loxTankDucer == 0);
    REQUIRE(data.kerTankDucer == 0);
    REQUIRE(data.purgeDucer == 0);
    REQUIRE(data.loxInletDucer == 0);
    REQUIRE(data.kerInletDucer == 0);
    REQUIRE(data.kerPintleDucer == 0);
    REQUIRE(data.loxVenturi == 0);
    REQUIRE(data.kerVenturi == 0);

    REQUIRE(data.pnematicsDucer == 0);

    //LOADCELL (lbf)
    REQUIRE(data.loadCell == 0);

    //TEMP SENSORS (C)
    REQUIRE(data.loxTank1 == 0);
    REQUIRE(data.loxTank2 == 0);
    REQUIRE(data.loxTank3 == 0);
    REQUIRE(data.loxDripLine == 0);
    REQUIRE(data.outsideThroat == 0);
    REQUIRE(data.nozzle == 0);
}