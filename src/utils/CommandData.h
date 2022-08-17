//
// Created by kevin on 2/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H

#include "ECSUtils.h"

/**
 * Class that contains a field for each effector. Represents expected
 * configuration after this command is applied
 */
struct CommandData {
    //TODO: maybe make a builder pattern for this? its a shit ton of parameters
    CommandData(ECSValveState loxVent, ECSValveState kerVent, ECSValveState loxDrip, ECSValveState kerDrip, ECSValveState loxPressurant,
                ECSValveState kerPressurant, ECSValveState loxFlow, ECSValveState kerFlow, ECSValveState loxPurge, ECSValveState kerPurge):
            loxVent(loxVent),
            kerVent(kerVent),
            loxDrip(loxDrip),
            kerDrip(kerDrip),
            loxPressurant(loxPressurant),
            kerPressurant(kerPressurant),
            loxFlow(loxFlow),
            kerFlow(kerFlow),
            loxPurge(loxPurge),
            kerPurge(kerPurge)
    {}

    CommandData() = default;

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
