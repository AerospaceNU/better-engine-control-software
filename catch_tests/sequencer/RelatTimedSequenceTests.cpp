//
// Created by kevin on 6/15/2022.
//


#include "../catch.hpp"
#include "sequencer/sequences/RelatTimedSequence.h"
#include "constants/HorizontalECSStates.h"
#include <vector>
#include <tuple>


TEST_CASE("RelatTimedSequence", "[unit]") {
    std::vector<IRedline*> redlines = {};
    ECSState state{"bruh", redlines, CommandData{}, CommandData{}};

    RelatTimedSequence seq{{{100, state}, {100, state}, {100, state}}};

    SECTION("Correct constructor"){
        int counter = 0;
        for (ISequence *i = &seq; i != nullptr; i = i->getNextSequence()) {
            REQUIRE(i->getStoredState().name == "bruh");
            counter++;
        }

        REQUIRE(counter == 3);
    }

    SECTION("Constructor throw on empty vector") {
        REQUIRE_THROWS_AS(
                RelatTimedSequence({}),
                std::out_of_range);
    }

    SECTION("Evaluating testCondition on various input times"){
        REQUIRE_FALSE(seq.testCondition(100, 99));
        REQUIRE_FALSE(seq.testCondition(100, 100));
        REQUIRE_FALSE(seq.testCondition(100, 101));
        REQUIRE_FALSE(seq.testCondition(100, 199));
        REQUIRE(seq.testCondition(100, 200));
    }
}


