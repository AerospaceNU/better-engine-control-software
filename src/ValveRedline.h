//
// Created by allison on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

#include "Redline.h"
#include "ECSUtils.h"

class ValveRedline: public Redline{
public:
    ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct, ECSValveState state);
    bool testCondition(SensorData* data);
    std::string errorMessage(SensorData* data);

protected:
    std::function<ECSValveState(SensorData*)> selector;
    ECSValveState state;
    //bool checkSame(ECSValveState s);
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
