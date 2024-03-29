//
// Created by kevin on 8/14/2022.
//

#include "../catch.hpp"
#include "utils/SensorData.h"

TEST_CASE("SensorData", "[unit]"){
    SensorData data;

    SECTION("Default constructor") {
        static_assert(SensorData::majorVersion == 7,
                      "Test not updated from SensorData change, please update this function and the static_assert");
        static_assert(CommandData::majorVersion == 4,
                      "Test not updated from CommandData change, please update this function and the static_assert");
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
        REQUIRE(data.kerOrifice == ECSValveState::INVALID);

        //PRESSURE SENSORS (psi)
        REQUIRE(data.orificeDownstreamDucer == 0);
        // REQUIRE(data.kerTankDucer == 0);
        // REQUIRE(data.purgeDucer == 0);
        // REQUIRE(data.loxInletDucer == 0);
        REQUIRE(data.kerInletDucer == 0);
        REQUIRE(data.kerPintleDucer == 0);
        REQUIRE(data.loxVenturi == 0);
        REQUIRE(data.loxVenturi2 == 0);
        REQUIRE(data.kerVenturi == 0);
        REQUIRE(data.kerVenturi2 == 0);

        REQUIRE(data.pneumaticDucer == 0);

        //LOADCELL (lbf)
        REQUIRE(data.loadCell == 0);

        REQUIRE(data.boardTemp == 0);

        //NEW VARIABLES
        REQUIRE(data.loxRegDucer == 0);
        REQUIRE(data.kerRegDucer == 0);
        // REQUIRE(data.n2pressDucer == 0);
        REQUIRE(data.orificeUpstreamDucer == 0);
        REQUIRE(data.loxTankTC == 0);
        REQUIRE(data.kerInletTC == 0);
        REQUIRE(data.kerOutletTC == 0);
        REQUIRE(data.miscTC == 0);

        REQUIRE(data.loxTankTC_Fault == 0);
        REQUIRE(data.kerInletTC_Fault == 0);
        REQUIRE(data.kerOutletTC_Fault == 0);
        REQUIRE(data.miscTC_Fault == 0);
    }
}
