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
    SensorDataCalibrator loadCell_calibration(INT_SELECTOR_FUNCT(loadCell),
                                               IntFuncts::Linear(-0.00108, 544));

    SensorDataCalibrator kerPintle_calibration(INT_SELECTOR_FUNCT(kerPintleDucer),
                                               IntFuncts::Linear(7630, 154564));

    SensorDataCalibrator loxReg_calibration(INT_SELECTOR_FUNCT(loxRegDucer),
                                                    IntFuncts::Linear(0.00794, 0.0214));

    SensorDataCalibrator kerReg_calibration(INT_SELECTOR_FUNCT(kerRegDucer),
                                                    IntFuncts::Linear(7913, -1628));

    SensorDataCalibrator loxTank_calibration(INT_SELECTOR_FUNCT(loxTankDucer),
                                                    IntFuncts::Linear(0.000127, -1.21));

    SensorDataCalibrator orificeUpstreamDucer_calibration(INT_SELECTOR_FUNCT(orificeUpstreamDucer),
                                                    IntFuncts::Linear(8271,  -226699));

    //SensorDataCalibrator orificeDownstreamDucer_calibration(INT_SELECTOR_FUNCT(orificeDownstreamDucer),
    //                                                IntFuncts::Linear(7897,  425));

    SensorDataCalibrator kerVenturi1_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                    IntFuncts::Linear(0.0079, 0.0143));

    SensorDataCalibrator kerVenturi2_calibration(INT_SELECTOR_FUNCT(kerVenturi2),
                                                 IntFuncts::Linear(0.000127, -3.11));
    
    SensorDataCalibrator loxVenturi1_calibration(INT_SELECTOR_FUNCT(loxVenturi),
                                                 IntFuncts::Linear(5763, 1430000));

    SensorDataCalibrator loxVenturi2_calibration(INT_SELECTOR_FUNCT(loxVenturi2),
                                                 IntFuncts::Linear(0.000128, 5.55));

    SensorDataCalibrator pnuematicDucer_calibration(INT_SELECTOR_FUNCT(pneumaticDucer),
                                               IntFuncts::Linear(61430, 1550000));
}

std::vector<SensorDataCalibrator> calibratorList = {
    loadCell_calibration,
    kerPintle_calibration,
    loxReg_calibration,
    kerReg_calibration,
    loxTank_calibration,
    orificeUpstreamDucer_calibration,
    //orificeDownstreamDucer_calibration,
    kerVenturi1_calibration,
    kerVenturi2_calibration,
    loxVenturi1_calibration,
    loxVenturi2_calibration,
    pnuematicDucer_calibration,
};
