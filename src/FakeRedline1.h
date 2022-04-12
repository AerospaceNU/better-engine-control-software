//
// Created by kevin on 3/28/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
#include "Redline.h"

class FakeRedline1: public Redline{
public:
    bool testCondition(SensorData data);

};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE1_H
