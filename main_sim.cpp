/**
* This file is the main file for building a complete ecs on regular computers, with a simulated CommBoundary
*/
#include <iostream>
#include "ecs/HorizontalECS.h"
#include "comm-boundary/ECSNetworker.h"
#include "phys-boundary/FakeBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/WatchDog.h"
#include "constants/AllECSStates.h"
#include "logger/Logger.h"
#include "src/utils/ECSUtils.h"

#include <chrono>
#include <thread>

//just declarations to get rid of compiler warnings
void run_ecs_forever(HorizontalECS* ecs);
void run_comm_forever(ECSNetworker* comm);

//void get_date();

void run_ecs_forever(HorizontalECS* ecs){
    //DO NOT CHANGE IT TO PASS BY REFERENCE, it breaks
    while(true){
        ecs->stepECS();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void run_comm_forever(ECSNetworker* comm){
    //DO NOT CHANGE IT TO PASS BY REFERENCE, it breaks
    while(true){
        comm->run();
    }
}

int main(){
    ECSNetworker networker;

    FakeBoundary boundary;

    WatchDog watchDog;

    Sequencer sequencer;

    // start logger with name ECS_LOG_<date>
    // only writes first row here does NOT write data until it reaches step ECS
    //TODO: add to real ECS not just sim, make it in something other than CWD for real ECS
    Logger logger = Logger("ECS_Log_"+get_date()+".csv");
    logger.init_csv();

    HorizontalECS ecs(networker, boundary, watchDog, sequencer, logger, ONLINE_SAFE_D, ONLINE_SAFE_D);

    networker.acceptECS(ecs);

    std::cout << "------------------------------------" << std::endl;
    std::cout << "Engine Control Software Version 1.0" << std::endl;
    std::cout << "SIMULATOR | NOT ACTUALLY CONNECTED TO STAND" << std::endl;
    std::cout << "Configuration: UNKNOWN (TODO)" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::thread ecs_thread(run_ecs_forever, &ecs);
    std::thread networker_thread(run_comm_forever, &networker);

    ecs_thread.join();
    networker_thread.join();
}