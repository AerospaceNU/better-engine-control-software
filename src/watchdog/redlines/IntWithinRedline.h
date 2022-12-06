#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H

#include "IRedline.h"
#include <functional>

/**
 * class to represent IRedline that checks for expected int value within a range
 */
class IntWithinRedline: public IRedline{
public:
    /*
     * We only allocate redlines at program start
     *
     * DO NOT CREATE NEW REDLINES AT RUNTIME, THIS WILL PROBABLY
     * GIVE US MEMORY ISSUES
     */
    IntWithinRedline(std::string name, std::function<int(SensorData&)>& sFunct, int lBound, int uBound,
                     ECSRedLineResponse r = ECSRedLineResponse::WARN);

    std::string getName() const override;

    /**
     * tests to make sure if passed sensor data falls into expected value
     * bounds are INCLUSIVE
     * @param data reference to sensor data object to read value from
     * @return true if within bounds, false otherwise
     */
    ECSRedLineResponse testCondition(SensorData& data) override;

    /**
     * creates a formatted error message string
     * @param data reference to sensor data object to read value from
     * @return string, containing IRedline name, expected value(s), and actual value
     */
    std::string errorMessage(SensorData& data) override;

    std::unique_ptr<IRedline> clone() override;
private:
    std::string name;

    /*
     * Might also be bit of a premature optimization, but the space saved by not copying the
     * selector function is like a hundred kilo-bytes
     */
    std::function<int(SensorData&)>& selector;

    int lowerBound;
    int upperBound;

    ECSRedLineResponse response;
};

/**
 * Factory method to create this type of redline
 */
std::unique_ptr<IntWithinRedline> RedlineFactory(std::string name,
                                                 std::function<int(SensorData&)>& selectorFunct,
                                                 int lowerBound,
                                                 int upperBound,
                                                 ECSRedLineResponse response = ECSRedLineResponse::WARN);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
