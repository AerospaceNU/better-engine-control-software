/**
* This file is the main file for building a complete ecs on the Raspberry Pi
*/
#include <iostream>
#include "ecs/StandECS.h"
#include "comm-boundary/SocketLogger.h"

#include "phys-boundary/packet-sources/PropBoardSource.h"
#include "phys-boundary/packet-sources/CrcChecking.h"
#include "phys-boundary/valves/ECSPiValve.h"
#include "phys-boundary/valves/ECSThreeWayPiValve.h"
#include "phys-boundary/TeensyBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/FakeWatchDog.h"
#include "constants/AllECSStates.h"
#include "constants/AllCalibrations.h"

#include <chrono>
#include <thread>
#include <utility>
#include <wiringPi.h>


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

    std::string propBoardLoc("/dev/serial/by-id/usb-STMicroelectronics_STM32_Virtual_ComPort_3463354A3135-if00");

    // Instantiate a SerialPort object
    LibSerial::SerialPort propBoardPort{propBoardLoc, LibSerial::BaudRate::BAUD_1152000};
    propBoardPort.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    propBoardPort.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    propBoardPort.SetParity(LibSerial::Parity::PARITY_NONE);
    propBoardPort.SetStopBits(LibSerial::StopBits::STOP_BITS_1);

    auto verificationFunct = [](const WrappedPacket<PropBoardSensorData>& d){
        return checkCrc(d);
    };

    auto propBoardSrc = std::make_unique<PropBoardSource>(std::move(propBoardPort), verificationFunct);


    wiringPiSetupGpio();
    TeensyBoundary boundary(std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 13),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 17),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 22),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 27),
                            std::make_unique<ECSPiValve>(ECSValveState::OPEN, 5),
                            std::make_unique<ECSPiValve>(ECSValveState::OPEN, 12),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 6),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 26),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 19),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 10),
                            std::make_unique<ECSPiValve>(ECSValveState::CLOSED, 9),
                            std::move(propBoardSrc),
                            calibratorList);

    FakeWatchDog watchDog;

    Sequencer sequencer;

    StandECS ecs(networker, boundary, watchDog, sequencer, ONLINE_SAFE_D);

    networker.acceptECS(ecs);


    std::cout << "------------------------------------" << std::endl;
    std::cout << "Better Engine Control Software Version 1.0" << std::endl;
    std::cout << "PI | WILL CONTROL STAND AND REPORT DATA FROM STAND" << std::endl;
    std::cout << "####" << std::endl;
    std::cout << "BE UNSAFE | BE DUMB" << std::endl;
    std::cout << "FOLLOW ALL GUIDELINES IN STANDARD OPERATING PROCEDURES" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::thread ecs_thread(run_ecs_forever, &ecs);
    std::thread networker_in_thread(run_comm_incoming_forever, &networker);
    std::thread networker_out_thread(run_comm_outgoing_forever, &networker);

    ecs_thread.join();
    networker_in_thread.join();
    networker_out_thread.join();
}
