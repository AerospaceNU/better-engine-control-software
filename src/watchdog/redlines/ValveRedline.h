#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

#include "IRedline.h"
#include <functional>

/**
 * class to represent IRedline that checks for an expected valve state
 */
class ValveRedline: public IRedline{
public:
    ValveRedline(std::string n, std::function<ECSValveState(SensorData&)>& sFunct, ECSValveState state);
    ValveRedline(std::string n, std::function<ECSValveState(SensorData&)>& sFunct,
                 ECSValveState state, ECSRedLineResponse res);

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data reference to sensor data object to read value from
     * @return true if valve reading matches expected, false otherwise
     */
    ECSRedLineResponse testCondition(SensorData& data) override;

    /**
     * creates a formatted error message string
     * @param data reference to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    std::string errorMessage(SensorData& data) override;

protected:
    ECSRedLineResponse response;

    std::function<ECSValveState(SensorData&)>& selector;
    std::string name;
    //ECSRedLineResponse response;

    //std::function<ECSValveState(SensorData&)> selector;
    ECSValveState expectedState;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
