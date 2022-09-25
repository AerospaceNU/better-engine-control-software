#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

#include "IRedline.h"
#include <functional>

/**
 * class to represent IRedline that checks for an expected valve state
 */
class ValveRedline: public IRedline{
public:
    /*
     * We only allocate redlines at program start
     *
     * DO NOT CREATE NEW REDLINES AT RUNTIME, THIS WILL PROBABLY
     * GIVE US MEMORY ISSUES
     */
    ValveRedline(std::string n, std::function<ECSValveState(SensorData&)>& sFunct,
                 ECSValveState state, ECSRedLineResponse res = ECSRedLineResponse::WARN);

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

private:
    std::string name;

    /*
     * Might also be bit of a premature optimization, but the space saved by not copying the
     * selector function is like a hundred kilo-bytes
     */
    std::function<ECSValveState(SensorData&)>& selector;

    ECSValveState expectedState;

    ECSRedLineResponse response;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
