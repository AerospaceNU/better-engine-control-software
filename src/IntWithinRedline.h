//
// Created by kevin on 4/11/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H

#include "Redline.h"
//#include <functional>
#include <string>
#include "SensorData.h"

class IntWithinRedline: public Redline{
public:
    IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int lBound, int uBound);
    IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int lBound, int uBound, ECSRedLineResponse r);
    bool testCondition(SensorData* data);
    std::string errorMessage(SensorData* data);

protected:
    std::function<int(SensorData*)> selector;
    int lowerBound;
    int upperBound;
    ECSRedLineResponse response;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
