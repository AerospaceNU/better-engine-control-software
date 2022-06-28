#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H

#include "SensorData.h"
#include <string>
#include "utils-and-constants/ECSUtils.h"

/**
 * An abstract class to represent IRedline object that checks sensor values
 * and verify that it is as expected
 */
class IRedline {
public :
    IRedline(std::string n, ECSRedLineResponse r):
        name(n),
        response(r)
    {}

    IRedline(std::string n):
        name(n),
        response(ECSRedLineResponse::WARN)
    {}

    std::string name;
    ECSRedLineResponse response;

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data Pointer to sensor data object to read value from
     * @return true if data passes expected, fail otherwise
     */
    virtual bool testCondition(SensorData* data) = 0;

    /**
     * creates a formatted error message string
     * @param data Pointer to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    virtual std::string errorMessage(SensorData* data) = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
