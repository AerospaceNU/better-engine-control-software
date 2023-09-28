//
// Created by kevin on 12/11/2022.
//

#include "../catch.hpp"
#include "watchdog/AverageWatchDog.h"
#include "watchdog/redlines/FakeRedline.h"
#include "utility"

TEST_CASE("AverageWatchDog constructors", "[unit]") {
    SensorData data;

    SECTION("Default constructor"){
        AverageWatchDog dog;
        REQUIRE(dog.stepRedlines(data).empty());
    }

    SECTION("Constructor stores list of redlines"){
        std::vector<std::unique_ptr<IRedline>> redlines;
        redlines.emplace_back(std::make_unique<FakeRedline>("bruh", ECSRedLineResponse::WARN));

        AverageWatchDog dog{std::move(redlines)};
        REQUIRE(dog.stepRedlines(data).size() == 1);
    }
    SECTION("Constructor filters null pointers"){
        std::vector<std::unique_ptr<IRedline>> redlines;
        redlines.emplace_back(std::unique_ptr<FakeRedline>());

        AverageWatchDog dog{std::move(redlines)};
        REQUIRE(dog.stepRedlines(data).empty());
    }

    SECTION("Constructor filters with valid and invalid redlines"){
        std::vector<std::unique_ptr<IRedline>> redlines;
        redlines.emplace_back(std::make_unique<FakeRedline>("bruh", ECSRedLineResponse::WARN));
        redlines.emplace_back(std::unique_ptr<FakeRedline>());

        AverageWatchDog dog{std::move(redlines)};
        REQUIRE(dog.stepRedlines(data).size() == 1);
    }
}

TEST_CASE("AverageWatchDog updateRedlines tests"){
    AverageWatchDog dog;
    SensorData data;

    SECTION("Update stores list of redlines"){
        std::vector<std::unique_ptr<IRedline>> redlines;
        redlines.emplace_back(std::make_unique<FakeRedline>("bruh", ECSRedLineResponse::WARN));

        dog.updateRedlines(std::move(redlines));
        REQUIRE(dog.stepRedlines(data).size() == 1);
    }

    SECTION("Update filters with valid and invalid redlines"){
        std::vector<std::unique_ptr<IRedline>> redlines;
        redlines.emplace_back(std::make_unique<FakeRedline>("bruh", ECSRedLineResponse::WARN));
        redlines.emplace_back(std::unique_ptr<FakeRedline>());

        dog.updateRedlines(std::move(redlines));
        REQUIRE(dog.stepRedlines(data).size() == 1);
    }
}

TEST_CASE("AverageWatchDog stepRedlines works"){
    std::vector<std::unique_ptr<IRedline>> redlines;
    redlines.emplace_back(std::make_unique<FakeRedline>("bruh1", ECSRedLineResponse::WARN));
    redlines.emplace_back(std::make_unique<FakeRedline>("bruh2", ECSRedLineResponse::ABORT));
    redlines.emplace_back(std::make_unique<FakeRedline>("bruh3", ECSRedLineResponse::SAFE));

    AverageWatchDog dog{std::move(redlines)};
    SensorData data;

    auto resultList = dog.stepRedlines(data);

    REQUIRE(resultList.size() == 3);

    auto& firstItem = resultList[0];
    REQUIRE(firstItem.response == ECSRedLineResponse::WARN);
    REQUIRE(firstItem.redlineName == "bruh1");

    auto& secondItem = resultList[1];
    REQUIRE(secondItem.response == ECSRedLineResponse::ABORT);
    REQUIRE(secondItem.redlineName == "bruh2");

    auto& thirdItem = resultList[2];
    REQUIRE(thirdItem.response == ECSRedLineResponse::SAFE);
    REQUIRE(thirdItem.redlineName == "bruh3");
}