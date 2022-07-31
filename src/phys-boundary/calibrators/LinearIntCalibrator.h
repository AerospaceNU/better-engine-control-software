//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H

#include "IntCalibrator.h"

class LinearIntCalibrator: public IntCalibrator{
public:
    LinearIntCalibrator(double m, double b);

    int applyCalibration(int rawValue) override;

private:
    double m;
    double b;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LINEARINTCALIBRATOR_H
