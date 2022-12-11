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

/*
 * this operator is deleted for a devious little reason
 *
 * we implement a CommandData == operator
 *
 * SensorData extends CommandData, which is useful to use the
 * CommandData == operator when comparing a SensorData from a certain config
 * represented by CommandData (see: our unit tests)
 *
 * However, the CommandData == operator will also SILENTLY accept
 * SensorData == SensorData, which is a bit risky because the CommandData
 * == obviously doesn't compare all the fields in SensorData
 *
 * So TDLR, we have a CommandData == which we want it to accept
 * a CommandData and a CommandData
 * a SensorData and a CommandData
 * a CommandData and a SensorData
 *
 * but not
 * SensorData and SensorData
 *
 * so we delete this operator explicitly
 *
 * we can just implement this operator== for SensorData later if we want,
 * but we just need to make sure the CommandData one doesn't randomly eat
 * SensorDatas when we aren't expecting it to
 */
bool operator==(SensorData& left, SensorData right) = delete;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H