//
// Created by allison on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

#include "Redline.h"
#include "ECSUtils.h"

/**
 * class to represent Redline that checks for an expected valve state
 */
class ValveRedline: public Redline{
public:
    ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct, ECSValveState state);
    ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct,
                 ECSValveState state, ECSRedLineResponse res);

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data Pointer to sensor data object to read value from
     * @return boolean
     */
    bool testCondition(SensorData* data);

    /**
     * creates a formatted error message string
     * @param data Pointer to sensor data object to read value from
     * @return string, containing Redline name, expected value(s), and actual value
     */
    std::string errorMessage(SensorData* data);

protected:
    std::function<ECSValveState(SensorData*)> selector;
    ECSValveState expectedState;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
