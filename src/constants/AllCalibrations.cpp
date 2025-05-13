//
// Created by kevin on 8/17/2022.
//

#include "AllCalibrations.h"
#include "utils/SensorData.h"
#include "phys-boundary/calibrators/SensorDataCalibrator.h"


/*
 * anonymous namespace to avoid collisions
 */
namespace {
    SensorDataCalibrator loadCell_calibration(INT_SELECTOR_FUNCT(loadCell),
                                               IntFuncts::Linear(-0.0005, 281));

    // SensorDataCalibrator kerPintle_calibration(INT_SELECTOR_FUNCT(kerPintleDucer),
    //                                            IntFuncts::Linear(0.000059, 22.4));

    SensorDataCalibrator loxReg_calibration(INT_SELECTOR_FUNCT(loxRegDucer),
                                                    IntFuncts::Linear(0.000127, 2.55));

    SensorDataCalibrator kerReg_calibration(INT_SELECTOR_FUNCT(kerRegDucer),
                                                    IntFuncts::Linear(0.000127, -0.863));

    // SensorDataCalibrator orificeDownstreamDucer_calibration(INT_SELECTOR_FUNCT(orificeDownstreamDucer),
    //                                                 IntFuncts::Linear(0.000127, -0.0799));

    // SensorDataCalibrator orificeUpstreamDucer_calibration(INT_SELECTOR_FUNCT(orificeUpstreamDucer),
    //                                                 IntFuncts::Linear(0.0138,  0.42));

    SensorDataCalibrator kerVenturi1_calibration(INT_SELECTOR_FUNCT(kerVenturi),
                                                    IntFuncts::Linear(0.000127, 0.122));

    SensorDataCalibrator kerVenturi2_calibration(INT_SELECTOR_FUNCT(kerVenturi2),
                                                 IntFuncts::Linear(0.000161, -236));
    
    SensorDataCalibrator loxVenturi1_calibration(INT_SELECTOR_FUNCT(loxVenturi),
                                                 IntFuncts::Linear(0.000163, -248));

    SensorDataCalibrator loxVenturi2_calibration(INT_SELECTOR_FUNCT(loxVenturi2),
                                                 IntFuncts::Linear(0.000163, -247));

    SensorDataCalibrator pnuematicDucer_calibration(INT_SELECTOR_FUNCT(pneumaticDucer),
                                               IntFuncts::Linear(0.0000164, -25.6));

    SensorDataCalibrator loxFlow_calibration(INT_SELECTOR_FUNCT(loxFlowDucer),
                                               IntFuncts::Linear(0.000128, -0.744));
    SensorDataCalibrator loxTank_calibration(INT_SELECTOR_FUNCT(loxTankDucer),
                                               IntFuncts::Linear(0.000126, -0.191));
    SensorDataCalibrator n2press_calibration(INT_SELECTOR_FUNCT(n2pressDucer),
                                               IntFuncts::Linear(0.000821, -1263));

    SensorDataCalibrator chamberDucer_calibration(INT_SELECTOR_FUNCT(chamberDucer),
                                               IntFuncts::Linear(0.000133, -255));

    SensorDataCalibrator kerFlowDucer_calibration(INT_SELECTOR_FUNCT(kerFlowDucer),
                                               IntFuncts::Linear(0.000165, -259));

    //add loxFlow, loxTank, n2press

}

std::vector<SensorDataCalibrator> calibratorList = {
    loadCell_calibration,
    // // kerPintle_calibration,
    loxReg_calibration,
    kerReg_calibration,
    // // orificeDownstreamDucer_calibration,
    // // orificeUpstreamDucer_calibration,
    kerVenturi1_calibration,
    kerVenturi2_calibration,
    kerFlowDucer_calibration,
    loxVenturi1_calibration,
    loxVenturi2_calibration,
    pnuematicDucer_calibration,
    chamberDucer_calibration,

    loxFlow_calibration,
    loxTank_calibration,
    n2press_calibration,
};

