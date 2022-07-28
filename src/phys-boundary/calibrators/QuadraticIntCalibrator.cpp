//
// Created by kevin on 7/26/2022.
//

#include "QuadraticIntCalibrator.h"

QuadraticIntCalibrator::QuadraticIntCalibrator(double a, double b, double c) :
    a(a),
    b(b),
    c(c)
{}

int QuadraticIntCalibrator::applyCalibration(int rawValue) {
    return c + (b * rawValue) + (a * rawValue * rawValue);
}
