//
// Created by kevin on 8/14/2022.
//

#include "../catch.hpp"
#include "watchdog/redlines/IntWithinRedline.h"

TEST_CASE("IntWithinRedline tests", "[bruh]"){
    //sensor data with 0 for all ints, and INVALID for all valves
    SensorData data;

    std::function<int(SensorData &)> loxTankDucerSelector = [](SensorData &data) { return data.loxTankDucer; };

    SECTION("Test condition with warn redline"){
        //testing default arg
        IntWithinRedline redline1("test", loxTankDucerSelector, 1, 2);
        REQUIRE(redline1.testCondition(data) == ECSRedLineResponse::WARN);

        IntWithinRedline redline2("test", loxTankDucerSelector, 1, 2, ECSRedLineResponse::WARN);
        REQUIRE(redline1.testCondition(data) == ECSRedLineResponse::WARN);
    }

    SECTION("Test condition with abort redline"){
        IntWithinRedline redline("test", loxTankDucerSelector, 1, 2, ECSRedLineResponse::ABORT);
        REQUIRE(redline.testCondition(data) == ECSRedLineResponse::ABORT);
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