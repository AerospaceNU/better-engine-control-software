//
// Created by kevin on 8/15/2022.
//

#include "../catch.hpp"
#include "phys-boundary/calibrators/IntCalibrator.h"

TEST_CASE("linear IntFunct", "[unit]"){
    SECTION("Identity calibrator"){
        IntToIntFunct calib = IntFuncts::linear(1, 0);

        REQUIRE(calib(30) == 30);
    }

    SECTION("All int calibrator"){
        IntToIntFunct calib = IntFuncts::linear(2, 1);

        REQUIRE(calib(50) == 101);
    }

    SECTION("All decimal calibrator"){
        // it is almost certain we will get janked by +/- 1 errors due to doubles rounding
        IntToIntFunct calib = IntFuncts::linear(0.5, 3.4);

        //also note, you can't really have or expressions in a REQUIRE(), unless you surround with parentheses
        REQUIRE(calib(50) == 28);
    }
}