//
// Created by kevin on 9/26/2022.
//
#include "../catch.hpp"
#include "comm-boundary/SocketLogger.h"
#include "ecs/FakeECS.h"

/**
 * These tests test the object's ability to parse jsons coming FROM the operator to the ECS
 *
 * The other direction, ECS to operator, is not tested (and tbh I don't wanna)
 *
 * Logging is not tested
 */

TEST_CASE("SocketLogger on totally bad JSONs", "[unit]") {
    FakeECS ecs;
    REQUIRE_FALSE(ecs.sequenceStarted);
    REQUIRE_FALSE(ecs.abortSequenceCalled);
    REQUIRE_FALSE(ecs.stateChanged);
    REQUIRE_FALSE(ecs.overrideCalled);
    REQUIRE_FALSE(ecs.abortCalled);

    SECTION("Missing JSON fields") {
        json command;
        command["command"] = "SET_ACTIVE_ELEMENTS";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);


        SocketLogger networker{Logger{}, q};

        networker.acceptECS(ecs);
        networker.processIncoming();

        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
    }

    SECTION("Invalid 'command' tag JSON") {
        json command;
        command["command"] = "BRUHHHHHHHH";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);


        SocketLogger networker{Logger{}, q};

        networker.acceptECS(ecs);
        networker.processIncoming();

        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
    }

    SECTION("Missing 'command' tag JSON") {
        json command;
        command["commandddddddd"] = "SET_ACTIVE_ELEMENTS";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);


        SocketLogger networker{Logger{}, q};

        networker.acceptECS(ecs);
        networker.processIncoming();

        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
    }
}

TEST_CASE("SocketLogger on override json command", "[unit]") {
    FakeECS ecs;
    REQUIRE_FALSE(ecs.sequenceStarted);
    REQUIRE_FALSE(ecs.abortSequenceCalled);
    REQUIRE_FALSE(ecs.stateChanged);
    REQUIRE_FALSE(ecs.overrideCalled);
    REQUIRE_FALSE(ecs.abortCalled);

    SECTION("Bad json inputs") {
        SECTION("Missing effectors") {
            json input = {
                    {"command", "SET_ACTIVE_ELEMENTS"},
                    {"activeElements", {
                           {"loxPressurant", "CLOSED"},
                           {"kerPressurant", "CLOSED"},
                           {"loxPurge", "CLOSED"},
                           {"kerPurge", "CLOSED"},
                           {"loxVent", "OPEN"},
                           {"kerVent", "OPEN"},
                           //{"loxFlow", "CLOSED"},
                           {"kerFlow", "CLOSED"}
                   }}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }

        SECTION("All effectors, but bad valve state"){
            json input = {
                    {"command", "SET_ACTIVE_ELEMENTS"},
                    {"activeElements", {
                                        {"loxPressurant", "CLOSED"},
                                        {"kerPressurant", "CLOSED"},
                                        {"loxPurge", "CLOSED"},
                                        {"kerPurge", "CLOSED"},
                                        {"loxVent", "OPEN"},
                                        {"kerVent", "OPEN"},
                                        {"loxFlow", "CLOSED"},
                                        {"kerFlow", "boogie"}
                                }}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }

        SECTION("Bad activeElements dict tag"){
            json input = {
                    {"command", "SET_ACTIVE_ELEMENTS"},
                    {"dogshuit", {
                                        {"loxPressurant", "CLOSED"},
                                        {"kerPressurant", "CLOSED"},
                                        {"loxPurge", "CLOSED"},
                                        {"kerPurge", "CLOSED"},
                                        {"loxVent", "OPEN"},
                                        {"kerVent", "OPEN"},
                                        {"loxFlow", "CLOSED"},
                                        {"kerFlow", "CLOSED"}
                                }}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }
    }

    SECTION("Working json"){
        json input = {
                {"command", "SET_ACTIVE_ELEMENTS"},
                {"activeElements", {
                                    {"loxPressurant", "CLOSED"},
                                    {"kerPressurant", "CLOSED"},
                                    {"loxDrip", "CLOSED"},
                                    {"kerDrip", "CLOSED"},
                                    {"loxPurge", "CLOSED"},
                                    {"kerPurge", "CLOSED"},
                                    {"loxVent", "OPEN"},
                                    {"kerVent", "OPEN"},
                                    {"loxFlow", "CLOSED"},
                                    {"kerFlow", "CLOSED"},
                                    {"kerOrifice", "CLOSED"}
                            }}
        };

        std::queue<json> q;
        q.push(input);

        SocketLogger comm(Logger{}, q);
        comm.acceptECS(ecs);

        comm.processIncoming();

        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.abortCalled);
        REQUIRE(ecs.overrideCalled);
    };
}

TEST_CASE("SocketLogger on state transition json command", "[unit]") {
    FakeECS ecs;
    REQUIRE_FALSE(ecs.sequenceStarted);
    REQUIRE_FALSE(ecs.abortSequenceCalled);
    REQUIRE_FALSE(ecs.stateChanged);
    REQUIRE_FALSE(ecs.overrideCalled);
    REQUIRE_FALSE(ecs.abortCalled);

    SECTION("Bad json inputs") {
        SECTION("Bad state name") {
            json input = {
                    {"command",  "SET_STATE"},
                    {"newState", "dogshit"}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }

        SECTION("Bad newState tag") {
            json input = {
                    {"command",  "SET_STATE"},
                    {"dogshit", "ONLINE_SAFE"}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }
    }

    SECTION("Working json") {
        /**
         * This test might be a bit flaky
         *
         * We have no way to provide the object with the
         * ECSStates available, those are found in ParsingHelpers
         *
         * So this test might require renaming the state name
         * as times change
         */

        json input = {
                {"command",  "SET_STATE"},
                {"newState", "ONLINE_SAFE_D"}
        };

        std::queue<json> q;
        q.push(input);

        SocketLogger comm(Logger{}, q);
        comm.acceptECS(ecs);

        comm.processIncoming();

        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
        REQUIRE(ecs.stateChanged);
    }
}

TEST_CASE("SocketLogger on start sequence command", "[unit]") {
    FakeECS ecs;
    REQUIRE_FALSE(ecs.sequenceStarted);
    REQUIRE_FALSE(ecs.abortSequenceCalled);
    REQUIRE_FALSE(ecs.stateChanged);
    REQUIRE_FALSE(ecs.overrideCalled);
    REQUIRE_FALSE(ecs.abortCalled);

    SECTION("Bad json inputs") {
        SECTION("Bad sequence name") {
            json input = {
                    {"command",  "START_SEQUENCE"},
                    {"sequence", "dogshit"}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }

        SECTION("Bad sequence tag") {
            json input = {
                    {"command",  "START_SEQUENCE"},
                    {"dogshit", "dogshit"}
            };

            std::queue<json> q;
            q.push(input);

            SocketLogger comm(Logger{}, q);
            comm.acceptECS(ecs);

            comm.processIncoming();

            REQUIRE_FALSE(ecs.sequenceStarted);
            REQUIRE_FALSE(ecs.abortSequenceCalled);
            REQUIRE_FALSE(ecs.stateChanged);
            REQUIRE_FALSE(ecs.overrideCalled);
            REQUIRE_FALSE(ecs.abortCalled);
        }
    }

    SECTION("Working json"){
        /**
         * This test might be a bit flaky
         *
         * We have no way to provide the networker object with the
         * sequences available, those are found in ParsingHelpers
         *
         * So this test might require renaming the sequence name
         * as times change
         */

        json input = {
                {"command",  "START_SEQUENCE"},
                {"sequence", "LOX_VENT_FLUTTER_x5"}
        };

        std::queue<json> q;
        q.push(input);

        SocketLogger comm(Logger{}, q);
        comm.acceptECS(ecs);

        comm.processIncoming();

        REQUIRE_FALSE(ecs.abortSequenceCalled);
        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
        REQUIRE(ecs.sequenceStarted);
    }
}

TEST_CASE("SocketLogger on abort sequence command", "[unit]") {
    FakeECS ecs;
    REQUIRE_FALSE(ecs.sequenceStarted);
    REQUIRE_FALSE(ecs.abortSequenceCalled);
    REQUIRE_FALSE(ecs.stateChanged);
    REQUIRE_FALSE(ecs.overrideCalled);
    REQUIRE_FALSE(ecs.abortCalled);

    SECTION("Working json"){
        json input = {
                {"command",  "ABORT_SEQUENCE"}
        };

        std::queue<json> q;
        q.push(input);

        SocketLogger comm(Logger{}, q);
        comm.acceptECS(ecs);

        comm.processIncoming();

        REQUIRE_FALSE(ecs.stateChanged);
        REQUIRE_FALSE(ecs.overrideCalled);
        REQUIRE_FALSE(ecs.abortCalled);
        REQUIRE_FALSE(ecs.sequenceStarted);
        REQUIRE(ecs.abortSequenceCalled);
    }
}

TEST_CASE("SocketLogger on abort command", "[unit]") {
    //TODO: implement this test when we get aborts implemented and a json format decided
    SUCCEED();
}
