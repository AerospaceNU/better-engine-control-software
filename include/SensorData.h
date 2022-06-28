#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H

#include "utils-and-constants/ECSUtils.h"

/**
 * Class that contains a field for each sensor and readable effector with their data
 */
class SensorData{
public:
    //REMOTELY CONTROLLED VALVES
    ECSValveState loxVent = ECSValveState::OPEN;
    ECSValveState kerVent = ECSValveState::CLOSED;
    ECSValveState loxDrip = ECSValveState::INVALID;
    ECSValveState kerDrip = ECSValveState::OPEN;
    ECSValveState loxPressurant = ECSValveState::CLOSED;
    ECSValveState kerPressurant = ECSValveState::INVALID;
    ECSValveState loxFlow = ECSValveState::OPEN;
    ECSValveState kerFlow = ECSValveState::CLOSED;
    ECSValveState loxPurge = ECSValveState::INVALID;
    ECSValveState kerPurge = ECSValveState::OPEN;

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