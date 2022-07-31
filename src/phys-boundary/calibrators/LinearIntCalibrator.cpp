//
// Created by kevin on 7/26/2022.
//

#include "LinearIntCalibrator.h"

LinearIntCalibrator::LinearIntCalibrator(double m, double b):
        m(m),
        b(b)
{}

int LinearIntCalibrator::applyCalibration(int rawValue) {
    return b + rawValue * m;
}

