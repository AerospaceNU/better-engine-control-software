//
// Created by kevin on 9/19/2022.
//

#include "../catch.hpp"
#include "comm-boundary/ParsingHelpers.h"

TEST_CASE("valveStateToString", "[unit]"){
    REQUIRE(valveStateToString(ECSValveState::OPEN) == "OPEN");
    REQUIRE(valveStateToString(ECSValveState::CLOSED) == "CLOSED");
    REQUIRE_THROWS_AS(stringToValveState(""), std::invalid_argument);
    REQUIRE_THROWS_AS(stringToECSState(""), std::invalid_argument);
}