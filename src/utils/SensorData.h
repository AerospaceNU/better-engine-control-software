#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H

#include "ECSUtils.h"
#include <array>
#include "CommandData.h"

/**
 * Class that contains a field for each sensor and readable effector with their data
 */
struct SensorData: public CommandData {
    static constexpr int majorVersion = 3;

    int loxTankDucer = 0;
    int kerTankDucer = 0;
    int purgeDucer = 0;
    int loxInletDucer = 0;
    int kerInletDucer = 0;
    int kerPintleDucer = 0;
    int loxVenturi = 0;
    int kerVenturi = 0;
    int loadCell = 0;
    int pneumaticDucer = 0;
    int loxRegDucer = 0;
    int kerRegDucer = 0;
    int n2pressDucer = 0;
    int loxTankTC = 0;
    int kerInletTC = 0;
    int kerOutletTC = 0;
    int miscTC = 0;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H