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
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
