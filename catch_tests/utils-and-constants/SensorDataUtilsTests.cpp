//
// Created by kevin on 10/17/2022.
//

#include "../catch.hpp"
#include "utils/SensorDataUtils.h"


TEST_CASE("SensorData median and mean tests", "[unit]"){
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    static_assert(SensorData::majorVersion == 3,
                  "Test not updated from SensorData change, please update this function and the static_assert");
    SECTION("Multiple SensorDatas"){
        SensorData data1;
        {
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
            data1.kerOrifice = ECSValveState::OPEN;

            data1.loxTankDucer = 5;
            data1.kerTankDucer = 7;
            data1.purgeDucer = 7;
            data1.loxInletDucer = 5;
            data1.kerInletDucer = 10;
            data1.kerPintleDucer = 10;
            data1.loxVenturi = 5;
            data1.kerVenturi = 7;
            data1.pneumaticDucer = 5;
            data1.loadCell = 5;
            data1.loxRegDucer = 5;
            data1.kerRegDucer = 7;
            data1.n2pressDucer = 10;
            data1.loxTankTC = 5;
            data1.kerInletTC = 7;
            data1.kerOutletTC = 10;
            data1.miscTC = 5;
        }

        SensorData data2;
        {
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
            data2.kerOrifice = ECSValveState::CLOSED;

            data2.loxTankDucer = 10;
            data2.kerTankDucer = 10;
            data2.purgeDucer = 5;
            data2.loxInletDucer = 7;
            data2.kerInletDucer = 5;
            data2.kerPintleDucer = 5;
            data2.loxVenturi = 7;
            data2.kerVenturi = 10;
            data2.pneumaticDucer = 10;
            data2.loadCell = 10;
            data2.loxRegDucer = 7;
            data2.kerRegDucer = 10;
            data2.n2pressDucer = 5;
            data2.loxTankTC = 7;
            data2.kerInletTC = 10;
            data2.kerOutletTC = 5;
            data2.miscTC = 7;
        }

        SensorData data3;
        {
            data3.loxVent = ECSValveState::CLOSED;
            data3.kerVent = ECSValveState::CLOSED;
            data3.loxDrip = ECSValveState::CLOSED;
            data3.kerDrip = ECSValveState::CLOSED;
            data3.loxPressurant = ECSValveState::CLOSED;
            data3.kerPressurant = ECSValveState::CLOSED;
            data3.loxFlow = ECSValveState::CLOSED;
            data3.kerFlow  = ECSValveState::CLOSED;
            data3.loxPurge = ECSValveState::CLOSED;
            data3.kerPurge = ECSValveState::CLOSED;
            data3.kerOrifice = ECSValveState::OPEN;

            data3.loxTankDucer = 7;
            data3.kerTankDucer = 5;
            data3.purgeDucer = 10;
            data3.loxInletDucer = 10;
            data3.kerInletDucer = 7;
            data3.kerPintleDucer = 7;
            data3.loxVenturi = 10;
            data3.kerVenturi = 5;
            data3.pneumaticDucer = 7;
            data3.loadCell = 7;
            data3.loxRegDucer = 10;
            data3.kerRegDucer = 5;
            data3.n2pressDucer = 7;
            data3.loxTankTC = 10;
            data3.kerInletTC = 5;
            data3.kerOutletTC = 7;
            data3.miscTC = 10;
        }

        SECTION("Median SensorData test"){
            std::vector<SensorData> input = {data1, data2, data3};

            SensorData result = medianData(input);

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
            REQUIRE(result.kerOrifice == ECSValveState::CLOSED);

            REQUIRE(result.loxTankDucer == 7);
            REQUIRE(result.kerTankDucer == 7);
            REQUIRE(result.purgeDucer == 7);
            REQUIRE(result.loxInletDucer == 7);
            REQUIRE(result.kerInletDucer == 7);
            REQUIRE(result.kerPintleDucer == 7);
            REQUIRE(result.loxVenturi == 7);
            REQUIRE(result.kerVenturi == 7);
            REQUIRE(result.pneumaticDucer == 7);
            REQUIRE(result.loadCell == 7);
            REQUIRE(result.loxRegDucer == 7);
            REQUIRE(result.kerRegDucer == 7);
            REQUIRE(result.n2pressDucer == 7);
            REQUIRE(result.loxTankTC == 7);
            REQUIRE(result.kerInletTC == 7);
            REQUIRE(result.kerOutletTC == 7);
            REQUIRE(result.miscTC == 7);
        }
    }

    SECTION("Empty SensorDatas"){
        std::vector<SensorData> empty_input;

        SensorData empty = medianData(empty_input);

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
        REQUIRE(empty.kerOrifice == ECSValveState::INVALID);

        REQUIRE(empty.loxTankDucer == 0);
        REQUIRE(empty.kerTankDucer == 0);
        REQUIRE(empty.purgeDucer == 0);
        REQUIRE(empty.loxInletDucer == 0);
        REQUIRE(empty.kerInletDucer == 0);
        REQUIRE(empty.kerPintleDucer == 0);
        REQUIRE(empty.loxVenturi == 0);
        REQUIRE(empty.kerVenturi == 0);
        REQUIRE(empty.loadCell == 0);
        REQUIRE(empty.pneumaticDucer == 0);
        REQUIRE(empty.loxRegDucer == 0);
        REQUIRE(empty.kerRegDucer == 0);
        REQUIRE(empty.n2pressDucer == 0);
        REQUIRE(empty.loxTankTC == 0);
        REQUIRE(empty.kerInletTC == 0);
        REQUIRE(empty.kerOutletTC == 0);
        REQUIRE(empty.miscTC == 0);
    }
}


TEST_CASE("SensorData average", "[unit]"){\
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    static_assert(SensorData::majorVersion == 3,
                  "Test not updated from SensorData change, please update this function and the static_assert");

    SensorData data1;
    data1.loxVent = ECSValveState::OPEN;
    data1.kerVent = ECSValveState::OPEN;
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
    data1.pneumaticDucer = 5;
    data1.loadCell = 5;
    data1.loxRegDucer = 5;
    data1.kerRegDucer = 5;
    data1.n2pressDucer = 5;
    data1.loxTankTC = 5;
    data1.kerInletTC = 5;
    data1.kerOutletTC = 5;
    data1.miscTC = 5;

    SensorData data2;
    data2.loxVent = ECSValveState::CLOSED;
    data2.kerVent = ECSValveState::CLOSED;
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
    data2.pneumaticDucer = 10;
    data2.loadCell = 10;
    data2.loxRegDucer = 10;
    data2.kerRegDucer = 10;
    data2.n2pressDucer = 10;
    data2.loxTankTC = 10;
    data2.kerInletTC = 10;
    data2.kerOutletTC = 10;
    data2.miscTC = 10;

    std::vector<SensorData> input = {data1, data2};

    SensorData result = averageData(input);

    REQUIRE(result.loxVent == ECSValveState::CLOSED);
    REQUIRE(result.kerVent == ECSValveState::CLOSED);
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
    REQUIRE(result.pneumaticDucer == 8);
    REQUIRE(result.loadCell == 8);
    REQUIRE(result.loxRegDucer == 8);
    REQUIRE(result.kerRegDucer == 8);
    REQUIRE(result.n2pressDucer == 8);
    REQUIRE(result.loxTankTC == 8);
    REQUIRE(result.kerInletTC == 8);
    REQUIRE(result.kerOutletTC == 8);
    REQUIRE(result.miscTC == 8);


    std::vector<SensorData> empty_input;

    SensorData empty = averageData(empty_input);

    REQUIRE(empty.loxVent == ECSValveState::INVALID);
    REQUIRE(empty.kerVent == ECSValveState::INVALID);
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
    REQUIRE(empty.pneumaticDucer == 0);
    REQUIRE(empty.loadCell == 0);
    REQUIRE(empty.loxRegDucer == 0);
    REQUIRE(empty.kerRegDucer == 0);
    REQUIRE(empty.n2pressDucer == 0);
    REQUIRE(empty.loxTankTC == 0);
    REQUIRE(empty.kerInletTC == 0);
    REQUIRE(empty.kerOutletTC == 0);
    REQUIRE(empty.miscTC == 0);
}
