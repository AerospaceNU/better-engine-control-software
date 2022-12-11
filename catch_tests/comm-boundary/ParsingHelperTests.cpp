//
// Created by kevin on 9/19/2022.
//

#include "../catch.hpp"
#include "comm-boundary/ParsingHelpers.h"

TEST_CASE("valveStateToString tests", "[unit]"){
    REQUIRE(valveStateToString(ECSValveState::OPEN) == "OPEN");
    REQUIRE(valveStateToString(ECSValveState::CLOSED) == "CLOSED");
}

TEST_CASE("stringToValveState tests", "[unit]"){
    REQUIRE_THROWS_AS(stringToValveState(""), std::invalid_argument);
}

TEST_CASE("stringToECSState tests", "[unit]"){
    SECTION("Throws std::invalid_argument on non-matching name"){
        REQUIRE_THROWS_AS(stringToECSState(""), std::invalid_argument);
    }

    /*
     * This test might require manual changes as we switch stand/rocket configurations
     */
    SECTION("Returns proper state on match"){
        REQUIRE(stringToECSState("ONLINE_SAFE").getName() == "ONLINE_SAFE");
    }
}

TEST_CASE("stringToSequence tests", "[unit]"){
    REQUIRE_THROWS_AS(stringToSequence(""), std::invalid_argument);
}