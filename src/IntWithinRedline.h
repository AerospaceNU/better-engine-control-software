//
// Created by kevin on 4/11/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H

#include "Redline.h"
//#include <functional>
#include <string>
#include "SensorData.h"

/**
 * class to represent Redline that checks for expected int value within a range
 */
class IntWithinRedline: public Redline{
public:
    IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int lBound, int uBound);
    IntWithinRedline(std::string n, std::function<int(SensorData*)> sFunct, int lBound, int uBound,
                     ECSRedLineResponse r);

    /**
     * tests to make sure if passed sensor data falls into expected value
     * bounds are INCLUSIVE
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
    std::function<int(SensorData*)> selector;
    int lowerBound;
    int upperBound;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTWITHINREDLINE_H
