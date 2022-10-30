//
// Created by kevin on 8/19/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H

#include <functional>
#include "utils/SensorData.h"


/**
 * Helper macros to abstract the repetitive parts of required lambdas
 */
#define CALIBRATION_FUNCT(LINE) [](SensorData &data) {\
                                    LINE\
                                }

#define INT_SELECTOR_FUNCT(LINE) [](SensorData& data) -> int& { \
                                    return LINE;   \
                                 }

/**
 * Class that applies a calibration to a given SensorData object
 *
 * It's basically just an encapsulated lambda function
 */
class SensorDataCalibrator {
public:
    SensorDataCalibrator(std::function<int&(SensorData&)> selector,
                         std::function<int(int)> calibrationFormula);
    explicit SensorDataCalibrator(std::function<void(SensorData&)> fieldMutator);

    /**
     * Application function, this will very likely mutate the passed in data
     * @param data data to be tweaked
     */
    void applyCalibration(SensorData& data);
private:
    std::function<void(SensorData&)> fieldMutator;
};


/**
 * These are convenience functions for describing a function on a int
 */
namespace IntFuncts {
    /**
     * Produces a function from int to int that applies the formula
     * a(x^2) + b(x) + c to any x
     *
     * @param a
     * @param b
     * @param c
     * @return a std::function<int(int)>
     */
    std::function<int(int)> Quadratic(double a, double b, double c);

    /**
     * Produces a function from int to int that applies the formula
     * m(x) + b to any x
     *
     * @param m
     * @param b
     * @return a std::function<int(int)>
     */
    std::function<int(int)> Linear(double m, double b);
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H
