//
// Created by kevin on 8/15/2022.
//

#include "../catch.hpp"
#include "phys-boundary/calibrators/QuadraticIntCalibrator.h"

TEST_CASE("QuadraticIntCalibrator", "[bruh]"){
    SECTION("Identity calibrator"){
        QuadraticIntCalibrator calib{0, 1, 0};

        REQUIRE(calib.applyCalibration(30) == 30);
    }

    SECTION("All int calibrator"){
        QuadraticIntCalibrator calib{1, 2, 1};

        REQUIRE(calib.applyCalibration(50) == 2601);
    }

    SECTION("All decimal calibrator"){
        // it is almost certain we will get janked by +/- 1 errors due to doubles rounding
        QuadraticIntCalibrator calib{1.5, 0.5, 3.4};

        //also note, you can't really have or expressions in a REQUIRE(), unless you surround with parentheses
        REQUIRE(calib.applyCalibration(50) == 3778);
    }
}