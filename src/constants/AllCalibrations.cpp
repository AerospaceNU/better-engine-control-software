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
    SensorDataCalibrator loadCell_calibration(&SensorData::loadCell,
                                               IntFuncts::Linear(-0.00108, 544));

    SensorDataCalibrator kerPintle_calibration(&SensorData::kerPintleDucer,
                                               IntFuncts::Linear(0.00792, -0.00264));

    SensorDataCalibrator loxReg_calibration(&SensorData::loxRegDucer,
                                                    IntFuncts::Linear(0.000127, 2.55));

    SensorDataCalibrator kerReg_calibration(&SensorData::kerRegDucer,
                                                    IntFuncts::Linear(0.00773, 0.0143));

    SensorDataCalibrator orificeDownstreamDucer_calibration(&SensorData::orificeDownstreamDucer,
                                                    IntFuncts::Linear(0.00748, -0.0351));

    SensorDataCalibrator orificeUpstreamDucer_calibration(&SensorData::orificeUpstreamDucer,
                                                    IntFuncts::Linear(0.0138,  0.42));

    SensorDataCalibrator kerVenturi1_calibration(&SensorData::kerVenturi,
                                                    IntFuncts::Linear(0.00795, -0.0922));

    SensorDataCalibrator kerVenturi2_calibration(&SensorData::kerVenturi2,
                                                 IntFuncts::Linear(0.00793, -0.0383));
    
    SensorDataCalibrator loxVenturi1_calibration(&SensorData::loxVenturi,
                                                 IntFuncts::Linear(0.00622, 1.47));

    SensorDataCalibrator loxVenturi2_calibration(&SensorData::loxVenturi2,
                                                 IntFuncts::Linear(0.00771, 0.0576));

    SensorDataCalibrator pnuematicDucer_calibration(&SensorData::pneumaticDucer,
                                               IntFuncts::Linear(0.0616, 1.53));
}

std::vector<SensorDataCalibrator> calibratorList = {
    loadCell_calibration,
    kerPintle_calibration,
    loxReg_calibration,
    kerReg_calibration,
    orificeDownstreamDucer_calibration,
    orificeUpstreamDucer_calibration,
    kerVenturi1_calibration,
    kerVenturi2_calibration,
    loxVenturi1_calibration,
    loxVenturi2_calibration,
    pnuematicDucer_calibration,
};
