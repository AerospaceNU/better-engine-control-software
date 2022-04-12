//
// Created by kevin on 3/28/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
#include "Redline.h"

class FakeRedline1: public Redline{
public:
    //FakeRedline1(std::string n, int llimit, int ulimit);
    bool testCondition(SensorData* data);
    std::string name = "FUCK";

protected:
    int lowerLimit = 8;
    int upperLimit = 9;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
