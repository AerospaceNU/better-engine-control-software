//
// Created by kevin on 3/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H

#include "SensorData.h"
#include "string"

class Redline {
public :
    Redline(std::string name, int lowerLimit, int upperLimit);
    std::string name;
    int lowerLimit;
    int upperLimit;

    bool testCondition(SensorData data);

private :

};
