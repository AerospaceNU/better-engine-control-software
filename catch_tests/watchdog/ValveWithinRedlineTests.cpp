//
// Created by kevin on 10/24/2022.
//
#include "../catch.hpp"

#include "watchdog/redlines/ValveRedline.h"

TEST_CASE("ValveRedline test condition", "[unit]"){
    //sensor data with 0 for all ints, and INVALID for all valves
    SensorData exampleData;

    std::function<ECSValveState(SensorData &)> mockSelector = []([[maybe_unused]]SensorData &data) { return ECSValveState::CLOSED;};

    SECTION("Test condition with warn redline"){
        ValveRedline openRedline{"test", mockSelector, ECSValveState::OPEN};
        REQUIRE(openRedline.testCondition(exampleData) == ECSRedLineResponse::WARN);

        ValveRedline openRedline2{"test", mockSelector, ECSValveState::OPEN, ECSRedLineResponse::WARN};
        REQUIRE(openRedline2.testCondition(exampleData) == ECSRedLineResponse::WARN);

        ValveRedline closedRedline{"test", mockSelector, ECSValveState::CLOSED};
        REQUIRE(closedRedline.testCondition(exampleData) == ECSRedLineResponse::SAFE);
    }

    SECTION("Test condition with abort redline"){
        ValveRedline abortOpenRedline("test", mockSelector, ECSValveState::OPEN, ECSRedLineResponse::ABORT);
        REQUIRE(abortOpenRedline.testCondition(exampleData) == ECSRedLineResponse::ABORT);

        ValveRedline abortClosedRedline("test", mockSelector, ECSValveState::CLOSED, ECSRedLineResponse::ABORT);
        REQUIRE(abortClosedRedline.testCondition(exampleData) == ECSRedLineResponse::SAFE);
    }
}

TEST_CASE("ValveRedline clone method", "[unit]") {
    std::function<ECSValveState(SensorData &)> mockSelector = []([[maybe_unused]]SensorData &data) { return ECSValveState::CLOSED;};
    std::unique_ptr<IRedline> ptr;
    REQUIRE_FALSE(ptr);

    {
        ValveRedline redline{"test", mockSelector, ECSValveState::OPEN};
        REQUIRE(redline.getName() == "test");

        ptr = redline.clone();
        REQUIRE(ptr->getName() == "test");
    }

    REQUIRE(ptr);
    REQUIRE(ptr->getName() == "test");
}