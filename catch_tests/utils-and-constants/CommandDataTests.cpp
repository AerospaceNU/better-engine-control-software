//
// Created by kevin on 8/24/2022.
//

#include "../catch.hpp"
#include "utils/CommandData.h"

TEST_CASE("CommandData", "[unit]"){
    CommandData data;

    SECTION("Default constructor") {
        REQUIRE(data.loxVent == ECSValveState::INVALID);
        REQUIRE(data.loxVent == ECSValveState::INVALID);
        REQUIRE(data.kerVent == ECSValveState::INVALID);
        REQUIRE(data.loxPressurant == ECSValveState::INVALID);
        REQUIRE(data.kerPressurant == ECSValveState::INVALID);
        REQUIRE(data.loxFlow == ECSValveState::INVALID);
        REQUIRE(data.kerFlow == ECSValveState::INVALID);
        REQUIRE(data.loxPurge == ECSValveState::INVALID);
        REQUIRE(data.kerPurge == ECSValveState::INVALID);
    }

    SECTION("Equality function") {
        REQUIRE(CommandData{} == CommandData{});
        data.loxPurge = ECSValveState::CLOSED;
        REQUIRE_FALSE(data == CommandData{});
    }
}