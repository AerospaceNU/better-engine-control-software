//
// Created by kevin on 6/15/2022.
//


#include "../catch.hpp"
#include "sequencer/sequences/RelatTimedSequence.h"
#include "constants/HorizontalECSStates.h"
#include <vector>
#include <tuple>


TEST_CASE("RelatTimedSequence", "[unit]") {
    std::pair<uint64_t, ECSState &> tup(1, ONLINE_SAFE_D);
    std::vector<std::pair<uint64_t, ECSState &>> pair_vector = {tup, tup, tup};
    RelatTimedSequence seq(pair_vector);

    SECTION("Correct constructor"){
        int counter = 0;
        for (ISequence *i = &seq; i != nullptr; i = i->getNextSequence()) {
            REQUIRE(i->getStoredState().name == "ONLINE_SAFE_D");
            counter++;
        }

        REQUIRE(counter == 3);
    }

    SECTION("Constructor throw on empty vector") {
        REQUIRE_THROWS_AS(
                RelatTimedSequence({}),
                std::out_of_range);
    }
}


