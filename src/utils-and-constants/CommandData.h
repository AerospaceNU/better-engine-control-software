//
// Created by kevin on 2/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H

#include "utils-and-constants/ECSUtils.h"

/**
 * Class that contains a field for each effector. Represents expected
 * configuration after this command is applied
 */
class CommandData {
public:
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
