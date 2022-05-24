#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H

#include "utils-and-constants/ECSUtils.h"

class SensorData{
public:
    //REMOTELY CONTROLLED VALVES
    ECSValveState loxVent = OPEN;
    ECSValveState kerVent = CLOSED;
    ECSValveState loxDrip = INVALID;
    ECSValveState kerDrip = OPEN;
    ECSValveState loxPressurant = CLOSED;
    ECSValveState kerPressurant = INVALID;
    ECSValveState loxFlow = OPEN;
    ECSValveState kerFlow = CLOSED;
    ECSValveState loxPurge = INVALID;
    ECSValveState kerPurge = OPEN;

    //PRESSURE SENSORS (psi)
    int loxTankDucer = 15;
    int kerTankDucer = 15;
    int purgeDucer = 15;
    int loxInletDucer = 15;
    int manifoldInletDucer = 15;
    int kerInletDucer = 15;
    int loxVenturi = 15;
    int kerVenturi = 15;

    //LOADCELL (lbf)
    int loadCell = 15;

    //TEMP SENSORS (C)
    int loxTank1 = 25;
    int loxTank2 = 25;
    int loxTank3 = 25;
    int loxDripLine = 25;
    int outsideThroat = 25;
    int nozzle = 25;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H