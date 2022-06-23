//
// Created by Matthew Coughlin on 2/23/22.
//
#include "generic/IECS.h"
#include "generic/IPhysicalBoundary.h"
#include "FakeBoundary.h"
#include "TeensyBoundary.h"
#include <unistd.h>
#include "utils-and-constants/HorizontalECSRedlines.h"

#include "SensorData.h"
#include "WatchDog.h"
#include "HorizontalECS.h"
#include <iostream>

constexpr const char* const SERIAL_PORT_1 = "/dev/ttyACM0";

int main() {
    /*
    WatchDog w(&ONLINE_SAFE_D_REDLINES);

    SensorData data{};

    for(IRedline* redline :w.stepRedlines(&data)){
        std::cout << redline->errorMessage(&data) << std::endl;
    }
     */



    IPhysicalBoundary* boundary = new TeensyBoundary(SERIAL_PORT_1);
    while(true){
        std::cout << "SENSORDATA" << std::endl;

        SensorData data = boundary->readFromBoundary();
        std::cout << data.loxTankDucer << std::endl;
        std::cout << data.kerTankDucer << std::endl;
        std::cout << data.purgeDucer << std::endl;
        std::cout << data.loxInletDucer << std::endl;
        std::cout << data.manifoldInletDucer << std::endl;
        std::cout << data.kerInletDucer << std::endl;
        std::cout << data.loxVenturi << std::endl;
        std::cout << data.kerVenturi << std::endl;

        //LOADCELL (lbf)
        std::cout << data.loadCell << std::endl;

        //TEMP SENSORS (C)
        std::cout << data.loxTank1 << std::endl;
        std::cout << data.loxTank2 << std::endl;
        std::cout << data.loxTank3 << std::endl;
        std::cout << data.loxDripLine << std::endl;
        std::cout << data.outsideThroat << std::endl;
        std::cout << data.nozzle << std::endl;

        usleep(100000);
    }

    //IPhysicalBoundary* boundary = new FakeBoundary();

    return 0;
}