//
// Created by kevin on 8/17/2022.
//

#include "HorizontalCalibrations.h"

//TODO: to be finished later once we verify which sensors are actually on the stand
QuadraticIntCalibrator loxInletDucer_calibration{0.714, 0.0375, 0};
QuadraticIntCalibrator kerInletDucer_calibration{5.34, 0.0375, 0};
QuadraticIntCalibrator purgeDucer_calibration{-0.577, 0.0375, 0};
QuadraticIntCalibrator kerPintleDucer_calibration{-0.954, 0.0375, 0};
QuadraticIntCalibrator loxTankDucer_calibration{0.9087, 0.0377, 0};
QuadraticIntCalibrator kerTankDucer_calibration{0.365, 0.0376, 0};
QuadraticIntCalibrator pneumaticDucer_calibration{-0.0888, 0.0101, 0};

QuadraticIntCalibrator loxRegDucer_calibration{0, 1, 0};
QuadraticIntCalibrator kerRegDucer_calibration{0, 1, 0};

QuadraticIntCalibrator loxVenturi_calibration{-1.97, 0.019, 0};
QuadraticIntCalibrator kerVenturi_calibration{0.34, 0.019, 0};
QuadraticIntCalibrator manifoldInletThermo_calibration{0, 1, 0};
QuadraticIntCalibrator manifoldOutletThermo_calibration{0, 1, 0};
QuadraticIntCalibrator loxTank1_calibration{0, 1, 0};
QuadraticIntCalibrator loxTank2_calibration{0, 1, 0};
QuadraticIntCalibrator loxTank3_calibration{0, 1, 0};
QuadraticIntCalibrator loadCell_calibration{0, 1, 0};


/**
 * Helper method that
 * @return
 */
std::array<std::unique_ptr<IntCalibrator>, 16> generateCalibratorObjects(){
    return {std::make_unique<QuadraticIntCalibrator>(loxTankDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(kerTankDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(purgeDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(loxInletDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(kerInletDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(kerPintleDucer_calibration),
            std::make_unique<QuadraticIntCalibrator>(loxVenturi_calibration),
            std::make_unique<QuadraticIntCalibrator>(kerVenturi_calibration),


            std::make_unique<QuadraticIntCalibrator>(pneumaticDucer_calibration),

            std::make_unique<QuadraticIntCalibrator>(loadCell_calibration),

            //TEMP SENSORS (C)
            // not currently being measuring properly, ignore
            std::make_unique<QuadraticIntCalibrator>(loxTank1_calibration),
            std::make_unique<QuadraticIntCalibrator>(loxTank2_calibration),
            std::make_unique<QuadraticIntCalibrator>(loxTank3_calibration),
            std::make_unique<QuadraticIntCalibrator>(loxDripLine_calibration),
            std::make_unique<QuadraticIntCalibrator>(outsideThroat_calibration),
            std::make_unique<QuadraticIntCalibrator>(nozzle_calibration),
    };
}