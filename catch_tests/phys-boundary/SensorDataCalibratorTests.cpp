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

TEST_CASE("SensorDataCalibrator on int", "[unit]"){
    SensorData sampleData;
    REQUIRE(sampleData.loxTankDucer == 0);

    SECTION("General constructor") {
        SensorDataCalibrator calib(
                [](SensorData &data) {
                    data.loxTankDucer += 1;
                });

        calib.applyCalibration(sampleData);
        REQUIRE(sampleData.loxTankDucer == 1);
    }
    SECTION("Specific constructor") {
        SensorDataCalibrator calib([](SensorData& data) -> int& {return data.loxTankDucer;},
                                   [](int x) {return x+1;});

        calib.applyCalibration(sampleData);
        REQUIRE(sampleData.loxTankDucer == 1);
    }
}

TEST_CASE("Calibrator macro", "[unit]"){
    SensorData exampleData;
    
    REQUIRE(exampleData.loxTankDucer == 0);

    SensorDataCalibrator calib(
            CALIBRATION_FUNCT(data.loxTankDucer += 1;));

    calib.applyCalibration(exampleData);
    REQUIRE(exampleData.loxTankDucer == 1);


    auto funct = INT_SELECTOR_FUNCT(data.loxTankDucer);
    int& value = funct(exampleData);
    value = 123;
    REQUIRE(exampleData.loxTankDucer == 123);
}