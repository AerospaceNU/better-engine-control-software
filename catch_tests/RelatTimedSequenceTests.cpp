//
// Created by kevin on 6/15/2022.
//


#include "catch.hpp"
#include "RelatTimedSequence.h"
#include "utils-and-constants/HorizontalECSStates.h"
#include <vector>
#include <tuple>


TEST_CASE("RelatTimedSequence constructor", "[RelatTimedSequence, Sequence, ISequence]"){
    std::tuple<uint64_t, const ECSState&> fuck(1, ONLINE_SAFE_D);
    const std::vector<std::tuple<uint64_t, const ECSState&>> fuckshit = {fuck, fuck, fuck};
    RelatTimedSequence seq(&fuckshit);


    int counter = 0;
    for(const ISequence* i = &seq; i != nullptr; i = i->getNextSequence()){
        REQUIRE(i->getStoredState().name == "ONLINE_SAFE_D");
        counter++;
    }

    REQUIRE(counter == 3);
}


