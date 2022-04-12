//
// Created by kevin on 4/11/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H

#include "Redline.h"
#include <functional>
#include <string>
#include "SensorData.h"

class IntWithinRedline: public Redline{
public:
    IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int uBound, int lBound);
    std::string name;
    bool testCondition(SensorData* data);

protected:
    std::function<int(SensorData*)> selector;
    int upperBound;
    int lowerBound;
    bool checkWithin(int);
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
