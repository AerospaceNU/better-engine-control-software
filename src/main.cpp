//
// Created by Matthew Coughlin on 2/23/22.
//
#include "generic/IECS.h"
#include "generic/IPhysicalBoundary.h"
#include "FakeBoundary.h"
#include "TeensyBoundary.h"
#include "utils-and-constants/HorizontalECSRedlines.h"

#include "SensorData.h"
#include "WatchDog.h"
#include "HorizontalECS.h"
#include <iostream>

constexpr const char* const SERIAL_PORT_1 = "/dev/ttyACM0";

int main() {
    WatchDog w(&ONLINE_SAFE_D_REDLINES);

    SensorData data{};

    for(IRedline* redline :w.stepRedlines(&data)){
        std::cout << redline->errorMessage(&data) << std::endl;
    }

    IPhysicalBoundary* boundary = new TeensyBoundary(SERIAL_PORT_1);

    //IPhysicalBoundary* boundary = new FakeBoundary();

    return 0;
}