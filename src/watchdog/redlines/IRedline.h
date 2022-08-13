#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H

#include "utils-and-constants/SensorData.h"
#include <string>
#include "utils-and-constants/ECSUtils.h"

/**
 * An abstraction to represent an object that checks sensor values
 * and verify that it is as expected
 */
class IRedline {
public :
    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data reference to sensor data object to read value from
     * @return response of redline
     */
    virtual ECSRedLineResponse testCondition(SensorData& data) = 0;

    /**
     * creates a formatted error message string
     * @param data reference to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    virtual std::string errorMessage(SensorData& data) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IRedline() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
