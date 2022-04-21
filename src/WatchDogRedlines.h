//
// Created by kevin on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "Redline.h"
#include "SensorData.h"
#include "ValveRedline.h"
#include "IntWithinRedline.h"
#include "ECSUtils.h"
#include <vector>

const std::vector<Redline *> ONLINE_SAFE_D = {
        //REMOTELY CONTROLLED VALVES
        new ValveRedline("loxVent",
                         [](SensorData *data) { return data->loxVent; },
                         OPEN),
        new ValveRedline("kerVent",
                         [](SensorData *data) { return data->kerVent; },
                         OPEN),
        new ValveRedline("loxDrip",
                         [](SensorData *data) { return data->loxDrip; },
                         OPEN),
        new ValveRedline("kerDrip",
                         [](SensorData *data) { return data->kerDrip; },
                         OPEN),
        new ValveRedline("loxPressurant",
                         [](SensorData *data) { return data->loxPressurant; },
                         CLOSED),
        new ValveRedline("kerPressurant",
                         [](SensorData *data) { return data->kerPressurant; },
                         CLOSED),
        new ValveRedline("loxFlow",
                         [](SensorData *data) { return data->loxFlow; },
                         CLOSED),
        new ValveRedline("kerFlow",
                         [](SensorData *data) { return data->kerFlow; },
                         CLOSED),
        new ValveRedline("loxPurge",
                         [](SensorData *data) { return data->loxPurge; },
                         CLOSED),
        new ValveRedline("kerPurge",
                         [](SensorData *data) { return data->kerPurge; },
                         CLOSED),
        //PRESSURE SENSORS (psi)
        new IntWithinRedline("loxTankDucer",
                             [](SensorData *data) { return data->loxTankDucer; },
                             0, 15),
        new IntWithinRedline("kerTankDucer",
                             [](SensorData *data) { return data->kerTankDucer; },
                             0, 15),
        new IntWithinRedline("purgeDucer",
                             [](SensorData *data) { return data->purgeDucer; },
                             0, 500),
        new IntWithinRedline("loxInletDucer",
                             [](SensorData *data) { return data->loxInletDucer; },
                             0, 15),
        new IntWithinRedline("manifoldInletDucer",
                             [](SensorData *data) { return data->manifoldInletDucer; },
                             0, 15),
        new IntWithinRedline("kerInletDucer",
                             [](SensorData *data) { return data->kerInletDucer; },
                             0, 15),
        new IntWithinRedline("loxVenturi",
                             [](SensorData *data) { return data->loxVenturi; },
                             0, 15),
        new IntWithinRedline("kerVenturi",
                             [](SensorData *data) { return data->kerVenturi; },
                             0, 15),
        //LOADCELL (lbf)
        new IntWithinRedline("loadcell",
                             [](SensorData *data) { return data->loadCell; },
                             0, 15),
        //TEMP SENSORS (C)
        new IntWithinRedline("loxTank1",
                             [](SensorData *data) { return data->loxTank1; },
                             20, 30),
        new IntWithinRedline("loxTank2",
                             [](SensorData *data) { return data->loxTank2; },
                             20, 30),
        new IntWithinRedline("loxTank3",
                             [](SensorData *data) { return data->loxTank3; },
                             20, 30),
        new IntWithinRedline("loxDripLine",
                             [](SensorData *data) { return data->loxDripLine; },
                             20, 30),
        new IntWithinRedline("outsideThroat",
                             [](SensorData *data) { return data->outsideThroat; },
                             20, 30),
        new IntWithinRedline("nozzle",
                             [](SensorData *data) { return data->nozzle; },
                             20, 30),
        new IntWithinRedline("bhioewihfdsa",
                             [](SensorData *data) { return data->nozzle; },
                             20, 400, ABORT)
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
