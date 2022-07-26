/**
* This file is a main file for quickly getting something to run as a check
 *
 * Don't forget to update the ecs_quick executable in the CMake!
*/

#include <iostream>
#include "utils-and-constants/SensorData.h"
#include "watchdog/WatchDog.h"
#include "utils-and-constants/HorizontalECSRedlines.h"
#include <functional>
#include "external/json.hpp"

using json = nlohmann::json;

int main() {
    //std::function<ECSValveState(SensorData &)> loxVentSelector = [](SensorData &data) { return data.loxVent; };

    std::cout << "here";
    WatchDog w(ONLINE_SAFE_D_REDLINES);

    SensorData data{};

    for(std::tuple<ECSRedLineResponse, IRedline*> failedRedlinePair: w.stepRedlines(data)){
        ECSRedLineResponse failedResponse = std::get<0>(failedRedlinePair);
        IRedline* failedRedline = std::get<1>(failedRedlinePair);

        std::cout << failedRedline->errorMessage(data) << std::endl;
        //failedRedline->response;
        //failedRedline->errorMessage(curData);
        //TODO: process each failed redline in some way
    }


//
//
//    std::cout << "sizes" << std::endl;
//    std::cout << "Size of ECSRedLineResponse " << sizeof(ECSRedLineResponse) << std::endl;
//    std::cout << "Size of std::function<ECSValveState(SensorData&)> " << sizeof(std::function<ECSValveState(SensorData&)>) << std::endl;
//    std::cout << "Size of ECSValveState " << sizeof(ECSValveState) << std::endl;
//    std::cout << "Size of std::string " << sizeof(std::string) << std::endl;
//    std::cout << "Size of int " << sizeof(int) << std::endl;
//    std::cout << "Size of char* " << sizeof(char*) << std::endl;

    json report;
    report["shit"] = "ass";

    std::cout << report.dump(4);
    return 0;
}