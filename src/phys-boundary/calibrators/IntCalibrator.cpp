//
// Created by kevin on 8/19/2022.
//

#include "IntCalibrator.h"

#include <utility>

IntCalibrator::IntCalibrator(std::function<void(SensorData &)> fieldMutator):
    fieldMutator(std::move(fieldMutator))
{}

void IntCalibrator::applyCalibration(SensorData &data) {
    fieldMutator(data);
}

IntToIntFunct IntFuncts::quadratic(double a, double b, double c){
    return [a,b,c](int x){return c + (b * x) + (a * x * x);};
}

IntToIntFunct IntFuncts::linear(double m, double b){
    return [m,b](int x){return b + x * m;};
}


