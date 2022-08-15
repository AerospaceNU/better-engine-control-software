//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H

#include "IntCalibrator.h"

/**
 * Object to apply a linear formula to a given int
 */
class LinearIntCalibrator: public IntCalibrator{
public:
    /**
     * Takes parameters of linear function
     * @param m slope
     * @param b y-intercept
     */
    LinearIntCalibrator(double m, double b);

    int applyCalibration(int rawValue) override;

private:
    double m;
    double b;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H
