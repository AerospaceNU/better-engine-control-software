//
// Created by kevin on 9/26/2022.
//
#include "../catch.hpp"
#include "comm-boundary/ECSNetworker.h"
#include "ecs/FakeECS.h"


TEST_CASE("Networker on bad JSONs", "[unit]"){
    /*
     * TODO: this unit test is ugly as shit
     * basically, destruction of the ECSNetworker errors (probably due to the websocket server)
     * this never occurs during actual operation bc we run infinitely
     * we probably have to properly close the server before the destructor
     *
     * our workaround is initializing the ECSNetworkers with new to avoid the destructor
     * this of course, memory leaks.
     *
     * lmao
     */

     SECTION("Missing JSON fields"){
        json command;
        command["command"] = "SET_ACTIVE_ELEMENTS";

        json activeEleInner;

        activeEleInner["loxPressurant"] = "OPEN";
        activeEleInner["kerPressurant"] = "CLOSED";

        command["activeElements"] = activeEleInner;

        std::queue<json> q;
        q.push(command);



        auto* networker = new ECSNetworker{q};
        FakeECS ecs;

        networker->acceptECS(ecs);
        networker->run();
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



        auto* networker = new ECSNetworker{q};
        FakeECS ecs;

        networker->acceptECS(ecs);
        networker->run();
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



        auto* networker = new ECSNetworker{q};
        FakeECS ecs;

        networker->acceptECS(ecs);
        networker->run();
    }
}
