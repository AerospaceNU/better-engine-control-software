//
// Created by kevin on 8/15/2022.
//

#include "../catch.hpp"
#include "phys-boundary/calibrators/SensorDataCalibrator.h"

TEST_CASE("Linear IntFunct", "[unit]"){
    SECTION("Identity calibrator"){
        std::function<int(int)> calib = IntFuncts::Linear(1, 0);

        REQUIRE(calib(30) == 30);
    }

    SECTION("All int calibrator"){
        std::function<int(int)> calib = IntFuncts::Linear(2, 1);

        REQUIRE(calib(50) == 101);
    }

    SECTION("All decimal calibrator"){
        // it is almost certain we will get janked by +/- 1 errors due to doubles rounding
        std::function<int(int)> calib = IntFuncts::Linear(0.5, 3.4);

        //also note, you can't really have or expressions in a REQUIRE(), unless you surround with parentheses
        REQUIRE(calib(50) == 28);
    }
}

TEST_CASE("Quadratic IntFunct", "[unit]"){
    SECTION("Identity calibrator"){
        std::function<int(int)> calib = IntFuncts::Quadratic(0, 1, 0);

        REQUIRE(calib(30) == 30);
    }

    SECTION("All int calibrator"){
        std::function<int(int)> calib = IntFuncts::Quadratic(1, 2, 1);

        REQUIRE(calib(50) == 2601);
    }

    SECTION("All decimal calibrator"){
        // it is almost certain we will get janked by +/- 1 errors due to doubles rounding
        std::function<int(int)> calib = IntFuncts::Quadratic(1.5, 0.5, 3.4);

        //also note, you can't really have or expressions in a REQUIRE(), unless you surround with parentheses
        REQUIRE(calib(50) == 3778);
    }
}

// TEST_CASE("SensorDataCalibrator on int", "[unit]"){
//     SensorData sampleData;
//     REQUIRE(sampleData.orificeDownstreamDucer == 0);

//     SECTION("General constructor") {
//         SensorDataCalibrator calib(
//                 [](SensorData &data) {
//                     data.orificeDownstreamDucer += 1;
//                 });

//         calib.applyCalibration(sampleData);
//         REQUIRE(sampleData.orificeDownstreamDucer == 1);
//     }
//     SECTION("Specific constructor") {
//         std::function<int&(SensorData&)> selectorFunct{[](SensorData& data) -> int& {return data.orificeDownstreamDucer;}};
//         std::function<int(const int&)> appFunct{[](const int& x) {return x+1;}};
//         SensorDataCalibrator calib(selectorFunct,
//                                    appFunct);

//         calib.applyCalibration(sampleData);
//         REQUIRE(sampleData.orificeDownstreamDucer == 1);
//     }
//     SECTION("Actual calibrator") {
//         sampleData.orificeDownstreamDucer = 2600000;
//         REQUIRE(sampleData.orificeDownstreamDucer == 2600000);
//         SensorDataCalibrator calib(INT_SELECTOR_FUNCT(orificeDownstreamDucer),
//                                                IntFuncts::Linear(0.0000163, -25.3));
//         calib.applyCalibration(sampleData);
//         REQUIRE(sampleData.orificeDownstreamDucer == 17);        
//     }
// }

// TEST_CASE("Calibrator macro", "[unit]"){
//     SensorData exampleData;
    
//     REQUIRE(exampleData.orificeDownstreamDucer == 0);

//     SensorDataCalibrator calib(
//             CALIBRATION_FUNCT(data.orificeDownstreamDucer += 1;));

//     calib.applyCalibration(exampleData);
//     REQUIRE(exampleData.orificeDownstreamDucer == 1);


//     auto funct = INT_SELECTOR_FUNCT(orificeDownstreamDucer);
//     int& value = funct(exampleData);
//     value = 123;
//     REQUIRE(exampleData.orificeDownstreamDucer == 123);
// }
