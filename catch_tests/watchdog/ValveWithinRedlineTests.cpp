//
// Created by kevin on 10/24/2022.
//
#include "../catch.hpp"

#include "watchdog/redlines/ValveRedline.h"

TEST_CASE("ValveRedline", "[unit]"){
    //sensor data with 0 for all ints, and INVALID for all valves
    SensorData data;

    std::function<ECSValveState(SensorData &)> mockSelector = [](SensorData &data) { return ECSValveState::CLOSED;};

    SECTION("Test condition with warn redline"){
        ValveRedline openRedline{"test", mockSelector, ECSValveState::OPEN};
        REQUIRE(openRedline.testCondition(data) == ECSRedLineResponse::WARN);

        ValveRedline openRedline2{"test", mockSelector, ECSValveState::OPEN, ECSRedLineResponse::WARN};
        REQUIRE(openRedline2.testCondition(data) == ECSRedLineResponse::WARN);

        ValveRedline closedRedline{"test", mockSelector, ECSValveState::CLOSED};
        REQUIRE(closedRedline.testCondition(data) == ECSRedLineResponse::SAFE);
    }

    SECTION("Test condition with abort redline"){
        ValveRedline abortOpenRedline("test", mockSelector, ECSValveState::OPEN, ECSRedLineResponse::ABORT);
        REQUIRE(abortOpenRedline.testCondition(data) == ECSRedLineResponse::ABORT);

        ValveRedline abortClosedRedline("test", mockSelector, ECSValveState::CLOSED, ECSRedLineResponse::ABORT);
        REQUIRE(abortClosedRedline.testCondition(data) == ECSRedLineResponse::SAFE);
    }
}