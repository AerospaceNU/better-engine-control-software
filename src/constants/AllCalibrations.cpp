//
// Created by kevin on 8/17/2022.
//

#include "AllCalibrations.h"
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
    SensorDataCalibrator loxTank_calibration(INT_SELECTOR_FUNCT(data.loxTankDucer),
                                             IntFuncts::Linear(0.0001259514766, 3.45631288));

    SensorDataCalibrator kerTank_calibration(INT_SELECTOR_FUNCT(data.kerTankDucer),
                                             IntFuncts::Linear(0.0001259949353, 2.462331832));

    SensorDataCalibrator loadCell_calibration(INT_SELECTOR_FUNCT(data.loadCell),
                                              IntFuncts::Linear(-0.0004724255085, 253.7309897));

    SensorDataCalibrator kerVenturi_calibration(INT_SELECTOR_FUNCT(data.kerVenturi),
                                                IntFuncts::Linear(0.00006588662394, -12.99229141));

    SensorDataCalibrator purgeDucer_calibraton(INT_SELECTOR_FUNCT(data.purgeDucer),
                                               IntFuncts::Linear(0.000126371319, -0.9242817509));

    SensorDataCalibrator loxInletDucer_calibration(INT_SELECTOR_FUNCT(data.loxInletDucer),
                                                   IntFuncts::Linear(0.0001261012973, 2.444621634));

    SensorDataCalibrator kerPintle_calibration(INT_SELECTOR_FUNCT(data.kerPintleDucer),
                                               (IntFuncts::Linear(0.0001264292329, 1.555186382)));

    SensorDataCalibrator kerInlet_calibration(INT_SELECTOR_FUNCT(data.kerInletDucer),
                                               (IntFuncts::Linear(0.0001263274958, 2.187590055)));

    SensorDataCalibrator kerReg_calibration(INT_SELECTOR_FUNCT(data.kerRegDucer),
                                              (IntFuncts::Linear(0.0001612867829, -244.281323)));

    SensorDataCalibrator loxReg_calibration(INT_SELECTOR_FUNCT(data.loxRegDucer),
                                            (IntFuncts::Linear(0.0001624871965, -247.0642206)));

    SensorDataCalibrator pneumaticDeucer_calibration(INT_SELECTOR_FUNCT(data.pneumaticDucer),
                                            (IntFuncts::Linear(0.00003165095416, 0.4254014892)));

    SensorDataCalibrator n2pressDeucer_calibration(INT_SELECTOR_FUNCT(data.n2pressDucer),
                                                     (IntFuncts::Linear(0.0007929082407, -1250.12311)));


}

std::vector<SensorDataCalibrator> calibratorList = {
        loxTank_calibration,
        kerTank_calibration,
        loadCell_calibration,
        kerVenturi_calibration,
        purgeDucer_calibraton,
        loxInletDucer_calibration,
        kerPintle_calibration,
        kerInlet_calibration,
        kerReg_calibration,
        loxReg_calibration,
        pneumaticDeucer_calibration,
        n2pressDeucer_calibration
};
