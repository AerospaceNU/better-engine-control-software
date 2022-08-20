//
// Created by kevin on 8/17/2022.
//

#include "HorizontalCalibrations.h"
#include "utils/SensorData.h"
#include <functional>
#include "phys-boundary/calibrators/SensorDataCalibrator.h"

/* copy pasted from the old ecs just for some examples
double loxInletDucer_calibration[3] = {0.714, 0.0375, 0};
double kerInletDucer_calibration[3] = {5.34, 0.0375, 0};
double purgeDucer_calibration[3] =  {-0.577, 0.0375, 0};
double kerPintleDucer_calibration[3] = {-0.954, 0.0375, 0};
double loxTankDucer_calibration[3] = {0.9087, 0.0377, 0};
double kerTankDucer_calibration[3] = {0.365, 0.0376, 0};
double pneumaticDucer_calibration[3] =  {-0.0888, 0.0101, 0};
double loxRegDucer_calibration[3] = {0, 1, 0};
double kerRegDucer_calibration[3] =  {0, 1, 0};
double loxVenturi_calibration[3] = {-1.97, 0.019, 0};
double kerVenturi_calibration[3] = {0.34, 0.019, 0};
double manifoldInletThermo_calibration[3] =  {0, 1, 0};
double manifoldOutletThermo_calibration[3] = {0, 1, 0};
double tank1Thermo_calibration[3] = {0, 1, 0};
double tank2Thermo_calibration[3] = {0, 1, 0};
double tank3Thermo_calibration[3] = {0, 1, 0};
double loadCell_calibration[3] = {0, 1, 0};
 */

/*
 * anonymous namespace to avoid collisions
 */
namespace {
    SensorDataCalibrator loxInletDucer_calibration(
            [](SensorData &data) {
                data.loxTankDucer = IntFuncts::Quadratic(0.714, 0.0375, 0)(data.loxTankDucer);
            });

    SensorDataCalibrator kerInletDucer_calibration(
            [](SensorData &data) {
                data.kerTankDucer = IntFuncts::Quadratic(5.34, 0.0375, 0)(data.kerTankDucer);
            });
}

std::vector<SensorDataCalibrator> calibratorList = {
        loxInletDucer_calibration,
        kerInletDucer_calibration
};



