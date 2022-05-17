#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H

#include "SensorData.h"
#include <string>
#include "ECSUtils.h"

/**
 * abstract class to represent Redline object, to check sensor value from SensorData
 * and verify that it falls into correct bounds
 */
class Redline {
public :
    // Redline(std::string name, int lowerLimit, int upperLimit);
    Redline(std::string n, ECSRedLineResponse r):
        name(n),
        response(r)
    {}

    Redline(std::string n):
        name(n),
        response(WARN)
    {}

    std::string name;
    ECSRedLineResponse response;

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data Pointer to sensor data object to read value from
     * @return boolean
     */
    virtual bool testCondition(SensorData* data) = 0;

    /**
     * creates a formatted error message string
     * @param data Pointer to sensor data object to read value from
     * @return string, containing Redline name, expected value(s), and actual value
     */
    virtual std::string errorMessage(SensorData* data) = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINE_H
