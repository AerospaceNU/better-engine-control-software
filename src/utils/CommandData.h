//
// Created by kevin on 2/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H

#include "ECSUtils.h"
struct SensorData;
/**
 * Class that contains a field for each effector. Represents expected
 * configuration after this command is applied
 */
struct CommandData {
    static constexpr int majorVersion = 1;

    CommandData(ECSValveState lVent, ECSValveState kVent, ECSValveState lDrip, ECSValveState kDrip, ECSValveState lPressurant,
                ECSValveState kPressurant, ECSValveState lFlow, ECSValveState kFlow, ECSValveState lPurge, ECSValveState kPurge = ECSValveState::INVALID):
            loxVent(lVent),
            kerVent(kVent),
            loxDrip(lDrip),
            kerDrip(kDrip),
            loxPressurant(lPressurant),
            kerPressurant(kPressurant),
            loxFlow(lFlow),
            kerFlow(kFlow),
            loxPurge(lPurge),
            kerPurge(kPurge)
    {}

    CommandData() = default;

    // deleted operators against possible object slicing
    CommandData(const SensorData &)=delete;
    CommandData &operator=(const SensorData &)=delete;

    //REMOTELY CONTROLLED VALVES
    ECSValveState loxVent = ECSValveState::INVALID;
    ECSValveState kerVent = ECSValveState::INVALID;
    ECSValveState loxDrip = ECSValveState::INVALID;
    ECSValveState kerDrip = ECSValveState::INVALID;
    ECSValveState loxPressurant = ECSValveState::INVALID;
    ECSValveState kerPressurant = ECSValveState::INVALID;
    ECSValveState loxFlow = ECSValveState::INVALID;
    ECSValveState kerFlow = ECSValveState::INVALID;
    ECSValveState loxPurge = ECSValveState::INVALID;
    ECSValveState kerPurge = ECSValveState::INVALID;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
