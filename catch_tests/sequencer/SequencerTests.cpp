//
// Created by kevin on 10/24/2022.
//

#include "../catch.hpp"

#include "sequencer/Sequencer.h"
#include "sequencer/sequences/RelatTimedSequence.h"

TEST_CASE("Sequencer tests", "[unit]"){
    Sequencer sequencer;

    ECSState state1{"bruh1", {}, CommandData{}, CommandData{}};
    ECSState state2{"bruh2", {}, CommandData{}, CommandData{}};

    RelatTimedSequence seq{{{100, state1}, {500, state2}}};

    SECTION("Not running at initialization") {
        REQUIRE_FALSE(sequencer.sequenceRunning());
    }

    SECTION("Setting and advancing a sequence") {
        sequencer.startSequence(1231, seq);
        REQUIRE(sequencer.sequenceRunning());

        REQUIRE_FALSE(sequencer.stepSequence(213));
        REQUIRE_FALSE(sequencer.stepSequence(1330));

        auto shouldBeValid = sequencer.stepSequence(1331);
        REQUIRE(shouldBeValid);
        REQUIRE(shouldBeValid->getName() == "bruh1");
        //new start time should be 1331 now

        REQUIRE_FALSE(sequencer.stepSequence(1830));

        shouldBeValid = sequencer.stepSequence(1831);
        REQUIRE(shouldBeValid);
        REQUIRE(shouldBeValid->getName() == "bruh2");

        REQUIRE_FALSE(sequencer.sequenceRunning());
    }

    SECTION("Testing sequencer aborts"){
        sequencer.startSequence(1231, seq);
        REQUIRE(sequencer.sequenceRunning());

        sequencer.abortSequence();
        REQUIRE_FALSE(sequencer.sequenceRunning());

        SECTION("Checking abort on already clear sequencer") {
            sequencer.abortSequence();
            REQUIRE_FALSE(sequencer.sequenceRunning());
        }
    }
}
