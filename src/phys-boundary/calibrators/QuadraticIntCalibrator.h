//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
#include "IntCalibrator.h"

class QuadraticIntCalibrator: public IntCalibrator{
public:
    QuadraticIntCalibrator(double a, double b, double c);

    int applyCalibration(int rawValue) override;

private:
    double a;
    double b;
    double c;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_QUADRATICINTCALIBRATOR_H
