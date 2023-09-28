/**
* This file is the main file for building a complete ecs on regular computers, with a simulated PhysBoundary
*/
#include <iostream>

#include "comm-boundary/SocketLogger.h"

#include "ecs/StandECS.h"
#include "phys-boundary/FakeBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/FakeWatchDog.h"
#include "constants/AllECSStates.h"
#include "logger/Logger.h"
#include "src/utils/ECSUtils.h"

#include <chrono>
#include <thread>

namespace {
    void run_ecs_forever(StandECS *ecs) {
        //DO NOT CHANGE IT TO PASS BY REFERENCE, it breaks
        while (true) {
            ecs->stepECS();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void run_comm_incoming_forever(SocketLogger *comm) {
        //DO NOT CHANGE IT TO PASS BY REFERENCE, it breaks
        while (true) {
            comm->processIncoming();
        }
    }

    void run_comm_outgoing_forever(SocketLogger *comm) {
        //DO NOT CHANGE IT TO PASS BY REFERENCE, it breaks
        while (true) {
            comm->processOutgoing();
        }
    }
}


int main(){
    Logger logger = Logger("ECS_Log_"+get_date()+".txt");

    SocketLogger networker{std::move(logger)};

    FakeBoundary boundary;

    FakeWatchDog watchDog;

    Sequencer sequencer;

    StandECS ecs(networker, boundary, watchDog, sequencer, ONLINE_SAFE_D);
    networker.acceptECS(ecs);

    std::thread ecs_thread(run_ecs_forever, &ecs);
    std::thread networker_in_thread(run_comm_incoming_forever, &networker);
    std::thread networker_out_thread(run_comm_outgoing_forever, &networker);

    std::cout << "------------------------------------" << std::endl;
    std::cout << "Engine Control Software Version 1.0" << std::endl;
    std::cout << "SIMULATOR | NOT ACTUALLY CONNECTED TO STAND" << std::endl;
    std::cout << "Configuration: UNKNOWN (TODO)" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    ecs_thread.join();
    networker_in_thread.join();
    networker_out_thread.join();
}
