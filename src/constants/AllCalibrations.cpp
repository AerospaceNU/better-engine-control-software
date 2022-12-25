//
// Created by kevin on 8/17/2022.
//

#include "AllCalibrations.h"
#include "utils/SensorData.h"
#include <functional>
#include "phys-boundary/calibrators/SensorDataCalibrator.h"


/*
 * anonymous namespace to avoid collisions
 */
namespace {
    SensorDataCalibrator loxTank_calibration(INT_SELECTOR_FUNCT(loxTankDucer),
                                             IntFuncts::Linear(0.0001259514766, 3.45631288));

    SensorDataCalibrator kerTank_calibration(INT_SELECTOR_FUNCT(kerTankDucer),
                                             IntFuncts::Linear(0.0001259949353, 2.462331832));

    SensorDataCalibrator loadCell_calibration(INT_SELECTOR_FUNCT(loadCell),
                                              IntFuncts::Linear(-0.0004724255085, 253.7309897));

    SensorDataCalibrator kerVenturi_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                IntFuncts::Linear(0.00006588662394, -12.99229141));

    SensorDataCalibrator purgeDucer_calibraton(INT_SELECTOR_FUNCT(purgeDucer),
                                               IntFuncts::Linear(0.000126371319, -0.9242817509));

    SensorDataCalibrator loxInletDucer_calibration(INT_SELECTOR_FUNCT(loxInletDucer),
                                                   IntFuncts::Linear(0.0001261012973, 2.444621634));

    SensorDataCalibrator kerPintle_calibration(INT_SELECTOR_FUNCT(kerPintleDucer),
                                               (IntFuncts::Linear(0.0001264292329, 1.555186382)));

    SensorDataCalibrator kerInlet_calibration(INT_SELECTOR_FUNCT(kerInletDucer),
                                               (IntFuncts::Linear(0.0001263274958, 2.187590055)));

    SensorDataCalibrator kerReg_calibration(INT_SELECTOR_FUNCT(kerRegDucer),
                                              (IntFuncts::Linear(0.0001612867829, -244.281323)));

    SensorDataCalibrator loxReg_calibration(INT_SELECTOR_FUNCT(loxRegDucer),
                                            (IntFuncts::Linear(0.0001624871965, -247.0642206)));

    SensorDataCalibrator pneumaticDeucer_calibration(INT_SELECTOR_FUNCT(pneumaticDucer),
                                            (IntFuncts::Linear(0.00003165095416, 0.4254014892)));

    SensorDataCalibrator n2pressDeucer_calibration(INT_SELECTOR_FUNCT(n2pressDucer),
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
