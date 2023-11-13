//
// Created by kevin on 12/7/2022.
//
#include "../catch.hpp"
#include "comm-boundary/FakeCommBoundary.h"
#include "phys-boundary/FakeBoundary.h"
#include "watchdog/FakeWatchDog.h"
#include "watchdog/redlines/FakeRedline.h"
#include "sequencer/Sequencer.h"
#include "sequencer/sequences/HangingSequence.h"
#include "utils/ECSState.h"

#include "ecs/StandECS.h"

#include <utility>

TEST_CASE("Basic commands on stand ECS", "[unit]"){
    FakeCommBoundary comm;
    FakeBoundary phys;
    FakeWatchDog watchdog;
    Sequencer sequencer;

    static_assert(CommandData::majorVersion == 4,
                      "Test not updated from CommandData change, please update this function and the static_assert");

    CommandData command{
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN
    };

    CommandData abortConfig{
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::CLOSED,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN
    };

    ECSState state{"state", {}, command, abortConfig};
    StandECS ecs{comm, phys, watchdog, sequencer, state};

    CommandData expectedConfig{
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED,
            ECSValveState::CLOSED
    };

    REQUIRE(phys.readFromBoundary() == expectedConfig);
    REQUIRE_FALSE(sequencer.sequenceRunning());

    SECTION("Manual override command"){
        ecs.acceptOverrideCommand(command);
        ecs.stepECS();

        REQUIRE(phys.readFromBoundary() == command);
    }

    SECTION("Change ECS state"){
        ecs.acceptStateTransition(state);
        ecs.stepECS();

        REQUIRE(phys.readFromBoundary() == command);
    }

    SECTION("Accept and end sequence"){
        HangingSequence seq{};
        ecs.acceptStartSequence(seq);
        ecs.stepECS();

        REQUIRE(sequencer.sequenceRunning());

        ecs.acceptAbortSequence();
        ecs.stepECS();
        REQUIRE_FALSE(sequencer.sequenceRunning());
    }

    SECTION("Accepting abort command"){
        ecs.acceptAbort();
        ecs.stepECS();

        REQUIRE(phys.readFromBoundary() == abortConfig);
    }
}

/**
* These tests validate the desired behaviors outlined on
 * https://docs.google.com/document/d/13wVZ21MutAXF1DjtOOyq3Rj8xwGjGRMDzKAMi2Bu1rk/edit?usp=sharing
*/

TEST_CASE("Stand ECS on sequencer tests", "[unit"){
    FakeCommBoundary comm;
    FakeBoundary phys;
    FakeWatchDog watchdog;
    Sequencer sequencer;

    static_assert(CommandData::majorVersion == 4,
                      "Test not updated from CommandData change, please update this function and the static_assert");

    CommandData data{
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN
    };

    ECSState state{"state", {}, data, data};
    StandECS ecs{comm, phys, watchdog, sequencer, state};

    REQUIRE_FALSE(sequencer.sequenceRunning());

    HangingSequence seq{};
    sequencer.startSequence(0, seq);
    REQUIRE(sequencer.sequenceRunning());

    SECTION("Sequencer stops on certain commands"){
        SECTION("Abort sequence command"){
            ecs.acceptAbortSequence();
            ecs.stepECS();
            REQUIRE_FALSE(sequencer.sequenceRunning());
        }
        SECTION("Abort command"){
            ecs.acceptAbort();
            ecs.stepECS();
            REQUIRE_FALSE(sequencer.sequenceRunning());
        }
    }
    SECTION("Sequencer ignores certain commands"){
        CommandData expectedConfig{
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED,
                ECSValveState::CLOSED
        };

        REQUIRE(phys.readFromBoundary() == expectedConfig);

        SECTION("Override command"){
            ecs.acceptOverrideCommand(data);
            ecs.stepECS();

            REQUIRE(sequencer.sequenceRunning());

            //ensure command isn't cached for after sequencer runs
            sequencer.abortSequence();
            ecs.stepECS();
            REQUIRE(phys.readFromBoundary() == expectedConfig);
        }
        SECTION("State change command"){
            ecs.acceptStateTransition(state);
            ecs.stepECS();

            REQUIRE(sequencer.sequenceRunning());

            //ensure command isn't cached for after sequencer runs
            sequencer.abortSequence();
            ecs.stepECS();
            REQUIRE(phys.readFromBoundary() == expectedConfig);
        }
    }
}

TEST_CASE("Stand ECS on redlines/watchdog", "[unit]"){
    FakeCommBoundary comm;
    FakeBoundary phys;
    FakeWatchDog watchdog;
    Sequencer sequencer;

    static_assert(CommandData::majorVersion == 4,
                      "Test not updated from CommandData change, please update this function and the static_assert");

    CommandData command{
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN,
            ECSValveState::OPEN
    };

    ECSState state{"state", {}, command, command};
    StandECS ecs{comm, phys, watchdog, sequencer, state};

    etl::vector<std::unique_ptr<IRedline>, 45> redlines{};
    redlines.emplace_back(std::make_unique<FakeRedline>("redline", ECSRedLineResponse::ABORT));

    watchdog.updateRedlines(std::move(redlines));

    SensorData data{};
    auto resultList = watchdog.stepRedlines(data);
    REQUIRE(resultList.size() == 1);
    REQUIRE(resultList[0].response == ECSRedLineResponse::ABORT);

    SECTION("Redlines preservation after manual override"){
        ecs.acceptOverrideCommand(command);
        ecs.stepECS();

        auto newResultList = watchdog.stepRedlines(data);
        REQUIRE(newResultList.size() == 1);
        REQUIRE(newResultList[0].response == ECSRedLineResponse::ABORT);
    }

    SECTION("Redlines removal after abort"){
        ecs.acceptAbort();
        ecs.stepECS();

        auto newResultList = watchdog.stepRedlines(data);
        REQUIRE(newResultList.empty());
    }
}
