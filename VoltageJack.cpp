//
// Created by kyle on 11/10/2025.
//
#include <cstdio>
#include <iostream>
#include <ostream>

#include "LabJackM.h"


class VoltageJack {
private:
    int error;
    int handle;
    char ErrorString[LJM_MAX_NAME_SIZE]{};
    double Value = 0;
    int LJMError = LJM_ReadLibraryConfigS(LJM_LIBRARY_VERSION, &Value);
    double volt0; // handles our voltage
    double volt1{};
    double volt2{};
    double volt3{};

public:
    // Constructor
    VoltageJack() : error(0), handle(0), volt0(0.0), volt1(0.0),
    volt2(0.0), volt3(0.0) {
        // Open the LabJack T7 device
        error = LJM_WriteLibraryConfigS("LJM_AUTO_RECONNECT_STICKY_CONNECTION", 1);
        if (error) {
            std::cout << ErrorString << "reconnecting" << std::endl;
        }
        error = LJM_OpenS("T7", "USB", "ANY", &handle);
        if (error != 0) {
            LJM_ErrorToString(error, ErrorString);
            printf("LJM_ReadLibraryConfigS error: %s\n", ErrorString);
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
        }
    }
    [[nodiscard]] int getHandle() const {
        return handle;
    }
    [[nodiscard]] double getVoltageAINO() const {
        return volt0;
    }
    [[nodiscard]] double getVoltageAINOne() const {
        return volt1;
    }
    [[nodiscard]] double getVoltageAINTwo() const {
        return volt2;
    }
    [[nodiscard]] double getVoltageAIN3() const {
        return volt3;
    }
    //goes up to 7 with T7 I believe. based off docs
    ~VoltageJack() {
        LJM_Close(handle);
    }

};