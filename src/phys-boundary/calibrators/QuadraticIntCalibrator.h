//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
#include "IntCalibrator.h"

/**
 * Object to apply a quadratic formula to a given int
 */
class QuadraticIntCalibrator: public IntCalibrator{
public:
    /**
     * Takes parameters of quadratic formula in form
     * a(x^2) + b(x) + c
     * @param a coefficient of x^2 term
     * @param b coefficient of x term
     * @param c y-intercept
     */
    QuadraticIntCalibrator(double a, double b, double c);

    int applyCalibration(int rawValue) override;

private:
    double a;
    double b;
    double c;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
