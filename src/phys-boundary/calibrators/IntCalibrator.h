//
// Created by kevin on 8/19/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H

#include <functional>
#include "utils/SensorData.h"

using IntToIntFunct = std::function<int(int)>;

//TODO: maybe template this class? something like Calibrator<T> in the future could be useful
class IntCalibrator {
public:
    IntCalibrator(std::function<void(SensorData&)> fieldMutator);

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
    IntToIntFunct quadratic(double a, double b, double c);

    /**
     * Produces a function from int to int that applies the formula
     * m(x) + b to any x
     *
     * @param m
     * @param b
     * @return a std::function<int(int)>
     */
    IntToIntFunct linear(double m, double b);
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
