//
// Created by kevin on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "Redline.h"
#include "ECSUtils.h"
#include <vector>


std::vector<Redline *> LOX_FILL_REDLINES;
std::vector<Redline *> ONLINE_SAFE_D;
ONLINE_SAFE_D = {
        new ValveRedline("loxVent", [](SensorData *data) { return data->sensor1Data; }, OPEN),
        new ValveRedline("kerVent", [](SensorData *data) { return data->sensor2Data; }, OPEN),
        new ValveRedline("loxDrip", [](SensorData *data) { return data->sensor3Data; }, OPEN),
        new ValveRedline("kerDrip", [](SensorData *data) { return data->sensor4Data; }, OPEN),
        new ValveRedline("loxPressurant", [](SensorData *data) { return data->sensor5Data; }, CLOSED),
        new ValveRedline("kerPressurant", [](SensorData *data) { return data->sensor6Data; }, CLOSED),
        new ValveRedline("loxFlow", [](SensorData *data) { return data->sensor7Data; }, CLOSED),
        new ValveRedline("kerFlow", [](SensorData *data) { return data->sensor8Data; }, CLOSED),
        new ValveRedline("loxPurge", [](SensorData *data) { return data->sensor9Data; }, CLOSED),
        new ValveRedline("kerPurge", [](SensorData *data) { return data->sensor10Data; }, CLOSED),
}


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
