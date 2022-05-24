#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H

#include "SensorData.h"
#include <string>
#include "utils-and-constants/ECSUtils.h"

/**
 * abstract class to represent IRedline object, to check sensor value from SensorData
 * and verify that it falls into correct bounds
 */
class IRedline {
public :
    // IRedline(std::string name, int lowerLimit, int upperLimit);
    IRedline(std::string n, ECSRedLineResponse r):
        name(n),
        response(r)
    {}

    IRedline(std::string n):
        name(n),
        response(WARN)
    {}

    std::string name;
    const ECSRedLineResponse response;

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data Pointer to sensor data object to read value from
     * @return boolean
     */
    virtual bool testCondition(const SensorData* data) = 0;

    /**
     * creates a formatted error message string
     * @param data Pointer to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    virtual std::string errorMessage(const SensorData* data) = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
