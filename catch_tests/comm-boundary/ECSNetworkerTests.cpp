//
// Created by kevin on 9/26/2022.
//
#include "../catch.hpp"
#include "comm-boundary/ECSNetworker.h"
#include <iostream>
#include "ecs/HorizontalECS.h"
#include "comm-boundary/ECSNetworker.h"
#include "phys-boundary/FakeBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/WatchDog.h"
#include "constants/HorizontalECSStates.h"

#include <chrono>
#include <thread>


TEST_CASE("Json parse", "[unit]"){
    json command;
    command["command"] = "SET_ACTIVE_ELEMENTS";

    json activeEleInner;

//    {
//        "activeElements": {
//            "kerFlow": "CLOSED",
//                    "kerPressurant": "CLOSED",
//                    "kerPurge": "CLOSED",
//                    "kerVent": "CLOSED",
//                    "loxFlow": "CLOSED",
//                    "loxPressurant": "OPEN",
//                    "loxPurge": "CLOSED",
//                    "loxVent": "CLOSED"
//        },
//        "command": "SET_ACTIVE_ELEMENTS"
//    }

    activeEleInner["loxPressurant"] = "OPEN";
    activeEleInner["kerPressurant"] = "CLOSED";

    activeEleInner["loxPurge"] = "CLOSED";
    activeEleInner["kerPurge"] = "CLOSED";

    activeEleInner["loxVent"] = "CLOSED";
    activeEleInner["kerVent"] = "CLOSED";

    activeEleInner["loxFlow"] = "CLOSED";
    activeEleInner["kerFlow"] = "CLOSED";

    activeEleInner["loxDrip"] = "CLOSED";
    activeEleInner["kerDrip"] = "CLOSED";

    command["activeElements"] = activeEleInner;

    std::queue<json> q;
    q.push(command);

    ECSNetworker networker{q};
    FakeBoundary boundary;

    WatchDog watchDog;

    Sequencer sequencer;

    HorizontalECS ecs(networker, boundary, watchDog, sequencer, ONLINE_SAFE_D, ONLINE_SAFE_D);

    networker.acceptECS(ecs);

    networker.run();
}