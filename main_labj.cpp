//
// Created by kyle on 11/10/2025.
//
/**
/* This file is the main file for building a complete ecs on the Raspberry Pi
/* was done before but data corrupted before commiting. Next step: reimplement voltage reading
/* from labjack and sending to teensy, then implement reading from teensy and sending to comms
*/
#include "ecs/StandECS.h"
#include "comm-boundary/SocketLogger.h"
#include "phys-boundary/packet-sources/PropBoardSource.h"
#include "phys-boundary/packet-sources/CrcChecking.h"
#include "phys-boundary/valves/ECSPiValve.h"
#include "phys-boundary/TeensyBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/FakeWatchDog.h"
#include "constants/AllECSStates.h"
#include "constants/AllCalibrations.h"

#include <chrono>
#include <iostream>
#include <thread>
#include <utility>
#include <wiringPi.h>
//#include "LabJackM.h" // testing library w/o raw serial port
#include <LabJackM.h>
#include "LJM_Utilities.h"
#include "VoltageJack.cpp"


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
	//int err;
	//int LJM_err_readings;
	// int handle;
	//open dt7 - model we are using. can do dtANY in order to use unknown versioon
	//err = LJM_Open(LJM_dtT7, LJM_ctANY, "LJM_idANY", &handle);

    VoltageJack vJack;
    std::cout << "Voltage on AIN0: " << vJack.getVoltageAINO()   << " V" << std::endl;
    std::cout << "Voltage on AIN1: " << vJack.getVoltageAINOne() << " V" << std::endl;
    std::cout << "Voltage on AIN2: " << vJack.getVoltageAINTwo() << " V" << std::endl;
    std::cout << "Voltage on AIN3: " << vJack.getVoltageAIN3()   << " V" << std::endl;

    //non-voltage readings:
	// if(err != LJME_NOERROR){
	// 	printf("Error in LJM_Open()\n");
	// 	return 1;
	// }
	// //confirm
	// printf("LJM_Open()\n");
	// get handle readings
    // int deviceType, connectionType, serialNumber, ipAddress, port, maxBytesPerMB;
	// LJM_err_readings = LJM_GetHandleInfo(handle, &deviceType, &connectionType, &serialNumber, 
    //                     &ipAddress, &port, &maxBytesPerMB);
	// if (LJM_err_readings != LJM_NOERROR){
	// 	printf("Error in LJM_GetHandleInfo()\n");
	// 	return 1;
	// }
	//close
	// LJM_Close(handle);
	// printf("LJM_Close()\n");
    
	// return 1;
 	//LJM_Open/LJM_OpenS will return the handle to that device if
 	//the DeviceType, ConnectionType, and Identifier - S = string, no S = int port connection


    Logger logger = Logger("ECS_Log_"+get_date()+".txt");

    SocketLogger networker{std::move(logger)};
	//tasks to do: find char sizes flow control parity etc on docs

    //std::string propBoardLoc("/dev/serial/by-id/usb-STMicroelectronics_STM32_Virtual_ComPort_3463354A3135-if00");

    // Instantiate a SerialPort object
    //change to be recieving from  labjacks and
    //send labjack source to teensy

    //LibSerial::SerialPort propBoardPort{propBoardLoc, LibSerial::BaudRate::BAUD_1152000};
    //propBoardPort.SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
    //propBoardPort.SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
    //propBoardPort.SetParity(LibSerial::Parity::PARITY_NONE);
    //propBoardPort.SetStopBits(LibSerial::StopBits::STOP_BITS_1);

    auto verificationFunct = [](const WrappedPacket<PropBoardSensorData>& d){
        return checkCrc(d);
    };
    // SerialPortSource labjackSource(handle, [](const WrappedPacket<LabJackSensorData>& d){
    //     return checkCrc(d);
    // }); - wrong implementation

    
    auto labJackSrc = std::make_unique<PropBoardSource>(vJack.getHandle, verificationFunct);


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
                            std::move(labJackSrc),
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

    //LJM_Close(handle); - use if no voltagejack
}
