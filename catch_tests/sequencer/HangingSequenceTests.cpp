//
// Created by kevin on 12/11/2022.
//

#include "../catch.hpp"
#include "sequencer/sequences/HangingSequence.h"

TEST_CASE("HangingSequence tests", "[unit]") {
    HangingSequence seq;

    SECTION("testCondition is always false"){
        REQUIRE_FALSE(seq.testCondition(0, 0));
        REQUIRE_FALSE(seq.testCondition(0, 10));
        REQUIRE_FALSE(seq.testCondition(10, 0));
    }

    SECTION("Throws on getStoredState"){
        REQUIRE_THROWS_AS(seq.getStoredState(),
                          std::out_of_range);
    }

    SECTION("Returns nullptr for next"){
        REQUIRE_FALSE(seq.getNextSequence());
    }
}