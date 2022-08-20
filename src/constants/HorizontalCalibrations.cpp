//
// Created by kevin on 8/17/2022.
//

#include "HorizontalCalibrations.h"
#include "utils/SensorData.h"
#include <functional>
#include "phys-boundary/calibrators/IntCalibrator.h"

IntToIntFunct asdas = [](int x) { return x * 2; };


IntCalibrator bruhShit(
        [](SensorData &data) {
            data.loxTankDucer = IntFormulas::quadratic(1, 1, 1)(data.loxTankDucer);
        });


std::function<int(int)> fuck([](int val) {
    return val * 2;
});

std::function<void(SensorData &, std::function<int(int)>)> loxTankDucerModifier([](SensorData &data,
                                                                                   std::function<int(int)> funct) {
    data.loxTankDucer = funct(data.loxTankDucer);
});



