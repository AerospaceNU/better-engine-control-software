//
// Created by kevin on 9/26/2022.
//
#include "../catch.hpp"
#include "comm-boundary/ECSNetworker.h"
#include "ecs/FakeECS.h"



TEST_CASE("Networker on bad JSONs", "[unit]"){
     SECTION("Missing JSON fields"){
        json command;
        command["command"] = "SET_ACTIVE_ELEMENTS";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);



        ECSNetworker networker{q};
        FakeECS ecs;

        networker.acceptECS(ecs);
        networker.run();
    }

    SECTION("Invalid 'command' tag JSON"){
        json command;
        command["command"] = "BRUHHHHHHHH";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);



        ECSNetworker networker{q};
        FakeECS ecs;

        networker.acceptECS(ecs);
        networker.run();
    }

    SECTION("Missing 'command' tag JSON"){
        json command;
        command["commandddddddd"] = "SET_ACTIVE_ELEMENTS";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);



        ECSNetworker networker{q};
        FakeECS ecs;

        networker.acceptECS(ecs);
        networker.run();
    }
}
