//
// Created by kevin on 12/11/2022.
//

#include "../catch.hpp"
#include "phys-boundary/valves/FakeECSValve.h"

TEST_CASE("FakeECSValve tests"){
    FakeECSValve valve{ECSValveState::CLOSED};

    SECTION("Returns correct state from construction"){
        REQUIRE(valve.getValveState() == ECSValveState::CLOSED);
    }

    SECTION("setValveState correctly mutates next get output"){
        REQUIRE(valve.getValveState() == ECSValveState::CLOSED);

        valve.setValveState(ECSValveState::OPEN);
        REQUIRE(valve.getValveState() == ECSValveState::OPEN);

    }

    SECTION("setValveState correctly throws"){
        REQUIRE_THROWS_AS(valve.setValveState(ECSValveState::INVALID),
                          EffectorException);
    }
}
