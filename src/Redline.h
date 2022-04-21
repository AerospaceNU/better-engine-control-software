//
// Created by kevin on 3/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H

#include "SensorData.h"
#include <string>
#include <functional>
#include "ECSUtils.h"

class Redline {
public :
    // Redline(std::string name, int lowerLimit, int upperLimit);
    Redline(std::string n, ECSRedLineResponse r):
        name(n),
        response(r)
    {}

    Redline(std::string n):
        name(n),
        response(WARN)
    {}

    std::string name;
    ECSRedLineResponse response;
    virtual bool testCondition(SensorData* data) = 0;
    virtual std::string errorMessage(SensorData* data) = 0;

    ECSRedLineResponse getResponse(){
        return response;
    }
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H
