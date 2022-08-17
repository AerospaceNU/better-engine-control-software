//
// Created by kevin on 8/17/2022.
//

//TODO: to be finished later once we verify which sensors are actually on the stand

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALCALIBRATIONS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALCALIBRATIONS_H

#include "phys-boundary/calibrators/IntCalibrator.h"
#include "phys-boundary/calibrators/QuadraticIntCalibrator.h"

#include <memory>
#include <array>

extern QuadraticIntCalibrator loxInletDucer_calibration;
extern QuadraticIntCalibrator kerInletDucer_calibration;
extern QuadraticIntCalibrator purgeDucer_calibration;
extern QuadraticIntCalibrator kerPintleDucer_calibration;
extern QuadraticIntCalibrator loxTankDucer_calibration;
extern QuadraticIntCalibrator kerTankDucer_calibration;
extern QuadraticIntCalibrator pneumaticDucer_calibration;
extern QuadraticIntCalibrator loxRegDucer_calibration;
extern QuadraticIntCalibrator kerRegDucer_calibration;
extern QuadraticIntCalibrator loxVenturi_calibration;
extern QuadraticIntCalibrator kerVenturi_calibration;
extern QuadraticIntCalibrator manifoldInletThermo_calibration;
extern QuadraticIntCalibrator manifoldOutletThermo_calibration;
extern QuadraticIntCalibrator loxTank1_calibration;
extern QuadraticIntCalibrator loxTank2_calibration;
extern QuadraticIntCalibrator loxTank3_calibration;
extern QuadraticIntCalibrator loadCell_calibration;

/**
 * Helper method that returns unique ptrs of calibrators for polymorphism
 *
 * The size of the array should directly match the number of int fields
 * in SensorData
 *
 * @return array of fixed length with all unique_ptrs
 */
std::array<std::unique_ptr<IntCalibrator>, 16> generateCalibratorObjects();

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALCALIBRATIONS_H
