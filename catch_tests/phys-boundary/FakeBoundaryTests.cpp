//
// Created by kevin on 8/12/2022.
//

#include "../catch.hpp"
#include "phys-boundary/FakeBoundary.h"

TEST_CASE("FakeBoundary", "[unit]"){
    FakeBoundary boundary;
    SensorData data = boundary.readFromBoundary();

    REQUIRE(data.loxVent == ECSValveState::CLOSED);
    REQUIRE(data.kerVent == ECSValveState::CLOSED);
    REQUIRE(data.loxPressurant == ECSValveState::CLOSED);
    REQUIRE(data.kerPressurant == ECSValveState::CLOSED);
    REQUIRE(data.loxFlow == ECSValveState::CLOSED);
    REQUIRE(data.kerFlow == ECSValveState::CLOSED);
    REQUIRE(data.loxPurge == ECSValveState::CLOSED);
    REQUIRE(data.kerPurge == ECSValveState::CLOSED);

    SECTION("Writing to boundary") {
        CommandData cmd{ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN};

        boundary.writeToBoundary(cmd);
        data = boundary.readFromBoundary();

        REQUIRE(data.loxVent == ECSValveState::OPEN);
        REQUIRE(data.kerVent == ECSValveState::OPEN);
        REQUIRE(data.loxPressurant == ECSValveState::OPEN);
        REQUIRE(data.kerPressurant == ECSValveState::OPEN);
        REQUIRE(data.loxFlow == ECSValveState::OPEN);
        REQUIRE(data.kerFlow == ECSValveState::OPEN);
        REQUIRE(data.loxPurge == ECSValveState::OPEN);
        REQUIRE(data.kerPurge == ECSValveState::OPEN);
    }

    SECTION("Writing Invalid state throws"){
        CommandData cmd{ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::OPEN,
                        ECSValveState::INVALID};

        REQUIRE_THROWS_AS(boundary.writeToBoundary(cmd),
                          EffectorException);
    }
}
