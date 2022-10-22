/**
* This file is the main file for building a complete ecs on the Raspberry Pi
*/
#include <iostream>
#include "ecs/HorizontalECS.h"
#include "comm-boundary/ECSNetworker.h"

#include "phys-boundary/packet-sources/PropBoardSource.h"

#include "phys-boundary/TeensyBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/WatchDog.h"
#include "constants/HorizontalECSStates.h"

#include <chrono>
#include <thread>
#include <utility>

//just declarations to get rid of compiler warnings
void run_ecs_forever(HorizontalECS* ecs);
void run_comm_forever(ECSNetworker* comm);


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
    // print_size_as_warning<sizeof(PropBoardSensorData)>()();

    ECSNetworker networker;

    std::string propBoardLoc("/dev/serial/by-id/usb-STMicroelectronics_STM32_Virtual_ComPort_3573374F3335-if00");

    // Instantiate a SerialPort objects
    LibSerial::SerialPort propBoardPort{propBoardLoc};

    //temp function until we get crc checking up
    auto alwaysTrueFunct = []([[maybe_unused]] const WrappedPacket<PropBoardSensorData>& d){
        return true;
    };

    auto propBoardSrc = std::make_unique<PropBoardSource>(std::move(propBoardPort), alwaysTrueFunct);

    TeensyBoundary boundary(std::move(propBoardSrc));

    WatchDog watchDog;

    Sequencer sequencer;

    Logger logger = Logger("ECS_Log_"+get_date()+".csv");
    logger.init_csv();

    HorizontalECS ecs(networker, boundary, watchDog, sequencer, logger, ONLINE_SAFE_D, ONLINE_SAFE_D);

    networker.acceptECS(ecs);


    std::cout << "------------------------------------" << std::endl;
    std::cout << "Engine Control Software Version 1.0" << std::endl;
    std::cout << "PI | WILL CONTROL STAND AND REPORT DATA FROM STAND" << std::endl;
    std::cout << "####" << std::endl;
    std::cout << "BE SAFE | BE SMART" << std::endl;
    std::cout << "FOLLOW ALL GUIDELINES IN STANDARD OPERATING PROCEDURES" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::thread ecs_thread(run_ecs_forever, &ecs);
    std::thread networker_thread(run_comm_forever, &networker);

    ecs_thread.join();
    networker_thread.join();
}