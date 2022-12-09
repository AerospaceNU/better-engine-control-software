#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H

#include "utils/SensorData.h"
#include <string>
#include "utils/ECSUtils.h"
#include <memory>

/**
 * An abstraction to represent an object that checks sensor values
 * and verify that it is as expected
 */
class IRedline {
public :
    /**
     * Returns name of redline object
     *
     * @return name
     */
    virtual std::string getName() const = 0;

    /**
     * tests to make sure if passed sensor data falls into expected value
     * @param data reference to sensor data object to read value from
     * @return response of redline
     */
    virtual ECSRedLineResponse testCondition(SensorData& data) = 0;

    /**
     * Returns a unique_ptr handle copy of this IRedline object
     *
     * This is necessary because we want to copy IRedlines, which are
     * polymorphic
     *
     * @return unique_ptr copy of this IRedline
     */
    virtual std::unique_ptr<IRedline> clone() = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IRedline() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IREDLINE_H
