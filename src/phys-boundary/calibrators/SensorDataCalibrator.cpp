//
// Created by kevin on 8/19/2022.
//

#include "SensorDataCalibrator.h"

#include <utility>

SensorDataCalibrator::SensorDataCalibrator(std::function<void(SensorData &)> fieldMut):
    fieldMutator(std::move(fieldMut))
{}

void SensorDataCalibrator::applyCalibration(SensorData &data) {
    fieldMutator(data);
}


std::function<int(const int&)> IntFuncts::Quadratic(double a, double b, double c){
    return [a,b,c](const int& x){
        return static_cast<int>(c + (b * x) + (a * x * x));
    };
}

std::function<int(const int&)> IntFuncts::Linear(double m, double b){
    return [m,b](const int& x){
        return static_cast<int>(b + x * m);
    };
}


