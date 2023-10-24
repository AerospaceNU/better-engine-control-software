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


    SensorDataCalibrator kerPintle_calibration(INT_SELECTOR_FUNCT(kerPintleDucer),
                                               IntFuncts::Linear(0.0000742, 26));

    SensorDataCalibrator loxReg_calibration(INT_SELECTOR_FUNCT(loxRegDucer),
                                                    IntFuncts::Linear(0.000127, 2.55));

    SensorDataCalibrator kerReg_calibration(INT_SELECTOR_FUNCT(kerRegDucer),
                                                    IntFuncts::Linear(0.00016, -235));

    SensorDataCalibrator loxTank_calibration(INT_SELECTOR_FUNCT(loxTankDucer),
                                                    IntFuncts::Linear(0.000127, -1.21));

    //IDK upstream of OV

    SensorDataCalibrator kerVenturi1_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                    IntFuncts::Linear(0.000127, -1.25));

    SensorDataCalibrator kerVenturi2_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                 IntFuncts::Linear(0.000127, -3.11));

    SensorDataCalibrator loxVenturi_calibration(INT_SELECTOR_FUNCT(loxVenturi),
                                                 IntFuncts::Linear(0.000128, 5.55));


    SensorDataCalibrator pnuematicDucer_calibration(INT_SELECTOR_FUNCT(pneumaticDucer),
                                               IntFuncts::Linear(0.0000163, -25.3));





}

std::vector<SensorDataCalibrator> calibratorList = {
//         loxTank_calibration,
//         kerTank_calibration,
//         loadCell_calibration,
//         kerVenturi_calibration,
//         purgeDucer_calibraton,
//         loxInletDucer_calibration,
//         kerPintle_calibration,
//         kerInlet_calibration,
//         kerReg_calibration,
//         loxReg_calibration,
//         pnuematicDucer_calibration,
//         n2pressDeucer_calibration
};
