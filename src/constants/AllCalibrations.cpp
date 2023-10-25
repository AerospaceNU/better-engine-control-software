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

    SensorDataCalibrator orificeUpstreamDucer_calibration(INT_SELECTOR_FUNCT(orificeUpstreamDucer),
                                                    IntFuncts::Linear(0.000126,  2.54));

    SensorDataCalibrator kerVenturi1_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                    IntFuncts::Linear(0.000127, -1.25));

    SensorDataCalibrator kerVenturi2_calibration(INT_SELECTOR_FUNCT(kerVenturi2),
                                                 IntFuncts::Linear(0.000127, -3.11));

    SensorDataCalibrator loxVenturi_calibration(INT_SELECTOR_FUNCT(loxVenturi),
                                                 IntFuncts::Linear(0.000128, 5.55));

    SensorDataCalibrator pnuematicDucer_calibration(INT_SELECTOR_FUNCT(pneumaticDucer),
                                               IntFuncts::Linear(0.0000163, -25.3));
}

std::vector<SensorDataCalibrator> calibratorList = {
        kerPintle_calibration,
        loxReg_calibration,
        kerReg_calibration,
        loxTank_calibration,
        orificeUpstreamDucer_calibration,
        kerVenturi1_calibration,
        kerVenturi2_calibration,
        loxVenturi_calibration,
        pnuematicDucer_calibration,
};
