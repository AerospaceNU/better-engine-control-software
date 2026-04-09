//
// Created by kyle on 11/10/2025.
//  in theory should handle th reading and writing of 
// our amps and voltages depending on what variables we want
// to use, and how many.
//
#include <cstdio>
#include <iostream>
#include <ostream>

#include "LabJackM.h"
#include "VoltageJack.h"


// Constructor
VoltageJack::VoltageJack() : error(0), handle(0), volt0(0.0), volt1(0.0),
volt2(0.0), volt3(0.0) {
    LJMError = LJM_ReadLibraryConfigS(LJM_LIBRARY_VERSION, &Value);
    std::printf("LJM_ReadLibraryConfigS(LJM_LIBRARY_VERSION) returned: %d\n", LJMError);
    // Open the LabJack T7 device
    error = LJM_WriteLibraryConfigS("LJM_AUTO_RECONNECT_STICKY_CONNECTION", 1);
    if (error) {
        std::cout << ErrorString << "reconnecting" << std::endl;
    }
    error = LJM_OpenS("T7", "USB", "ANY", &handle);
    if (error != 0) {
        LJM_ErrorToString(error, ErrorString);
        printf("LJM_OpenS error: %s\n", ErrorString);
    }

    // Read the voltage on AIN0
    if (error == 0) {
        error = LJM_eReadName(handle, "AIN0", &volt0);
        if (error == 0) {
            error = LJM_eReadName(handle, "AIN1", &volt1);
        }
        if (error == 0) {
            error = LJM_eReadName(handle, "AIN2", &volt2);
        }
        if (error == 0) {
            error = LJM_eReadName(handle, "AIN3", &volt3);
        }
        if(error == 0) {
            error = LJM_eReadName(handle, "AIN4", &amp1);
        }
    }
}

int VoltageJack::getHandle() const {
    return handle;
}

double VoltageJack::getVoltageAINO() const {
    return volt0;
}

double VoltageJack::getVoltageAINOne() const {
    return volt1;
}

double VoltageJack::getVoltageAINTwo() const {
    return volt2;
}

double VoltageJack::getVoltageAIN3() const {
    return volt3;
}

//use one output for amp - should have 7 since t7
double VoltageJack::getAmpsAIN4() const {
    return amp1;
}

//goes up to 7 with T7 I believe. based off docs
VoltageJack::~VoltageJack() {
    LJM_Close(handle);
}