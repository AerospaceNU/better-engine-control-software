//
// Created by kevin on 8/14/2022.
//

#include "../catch.hpp"
#include "watchdog/redlines/IntWithinRedline.h"

TEST_CASE("IntWithinRedline", "[unit]"){
    //sensor data with 0 for all ints, and INVALID for all valves
    SensorData data;

    std::function<int(SensorData &)> loxTankDucerSelector = [](SensorData &data) { return 0; };

    SECTION("Test condition with warn redline"){
        //testing default arg
        IntWithinRedline defaultRedline1_2("test", loxTankDucerSelector, 1, 2);
        REQUIRE(defaultRedline1_2.testCondition(data) == ECSRedLineResponse::WARN);

        IntWithinRedline redline1_2("test", loxTankDucerSelector, 1, 2, ECSRedLineResponse::WARN);
        REQUIRE(redline1_2.testCondition(data) == ECSRedLineResponse::WARN);

        IntWithinRedline redline_neg_1_1("test", loxTankDucerSelector, -1, 2, ECSRedLineResponse::WARN);
        REQUIRE(redline_neg_1_1.testCondition(data) == ECSRedLineResponse::SAFE);
    }

    SECTION("Test condition with abort redline"){
        IntWithinRedline redline1_2("test", loxTankDucerSelector, 1, 2, ECSRedLineResponse::ABORT);
        REQUIRE(redline1_2.testCondition(data) == ECSRedLineResponse::ABORT);

        IntWithinRedline redline_neg_1_1("test", loxTankDucerSelector, -1, 2, ECSRedLineResponse::ABORT);
        REQUIRE(redline_neg_1_1.testCondition(data) == ECSRedLineResponse::SAFE);
    }

    SECTION("Test constructor throw on invalid bounds"){
        REQUIRE_THROWS_AS(
                IntWithinRedline("test", loxTankDucerSelector, 1, 0, ECSRedLineResponse::ABORT),
                std::invalid_argument);

        REQUIRE_THROWS_AS(
                IntWithinRedline("test", loxTankDucerSelector, 1, 1, ECSRedLineResponse::ABORT),
                std::invalid_argument);
    }
}