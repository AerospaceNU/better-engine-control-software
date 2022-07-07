/**
* This file is a main file for quickly getting something to run as a check
 *
 * Don't forget to update the ecs_quick executable in the CMake!
*/

#include <iostream>
#include "utils-and-constants/SensorData.h"
#include "watchdog/WatchDog.h"
#include "utils-and-constants/HorizontalECSRedlines.h"


int main() {

    WatchDog w(&ONLINE_SAFE_D_REDLINES);

    SensorData data{};

    for(std::tuple<ECSRedLineResponse, IRedline*> failedRedlinePair: w.stepRedlines(&data)){
        ECSRedLineResponse failedResponse = std::get<0>(failedRedlinePair);
        IRedline* failedRedline = std::get<1>(failedRedlinePair);

        std::cout << failedRedline->errorMessage(&data) << std::endl;
        //failedRedline->response;
        //failedRedline->errorMessage(curData);
        //TODO: process each failed redline in some way
    }
}