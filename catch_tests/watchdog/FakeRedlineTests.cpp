//
// Created by kevin on 12/11/2022.
//

#include "../catch.hpp"
#include "watchdog/redlines/FakeRedline.h"

TEST_CASE("FakeRedlines tests", "[unit]"){
    FakeRedline redline{"bruh", ECSRedLineResponse::ABORT};

    REQUIRE(redline.getName() == "bruh");

    SECTION("Correct stored response returned"){
        REQUIRE(redline.testCondition(SensorData{}) == ECSRedLineResponse::ABORT);
    }

    SECTION("Clone method works"){
        std::unique_ptr<IRedline> ptr;
        REQUIRE_FALSE(ptr);

        {
            FakeRedline diffRedline{"bruh", ECSRedLineResponse::ABORT};
            REQUIRE(diffRedline.getName() == "bruh");
            REQUIRE(diffRedline.testCondition(SensorData{}) == ECSRedLineResponse::ABORT);

            ptr = diffRedline.clone();
            REQUIRE(ptr);
        }

        REQUIRE(ptr->getName() == "bruh");
        REQUIRE(ptr->testCondition(SensorData{}) == ECSRedLineResponse::ABORT);
    }
}