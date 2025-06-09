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



