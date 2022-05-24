#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

#include "generic/IRedline.h"
#include <functional>

/**
 * class to represent IRedline that checks for an expected valve state
 */
class ValveRedline: public IRedline{
public:
    ValveRedline(std::string n, std::function<ECSValveState(const SensorData*)> sFunct, ECSValveState state);
    ValveRedline(std::string n, std::function<ECSValveState(const SensorData*)> sFunct,
                 ECSValveState state, ECSRedLineResponse res);

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data Pointer to sensor data object to read value from
     * @return boolean
     */
    bool testCondition(const SensorData* data) override;

    /**
     * creates a formatted error message string
     * @param data Pointer to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    std::string errorMessage(const SensorData* data) override;

protected:
    std::function<ECSValveState(const SensorData*)> selector;
    ECSValveState expectedState;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
