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
    static constexpr int majorVersion = 2;
    CommandData(ECSValveState loxVent_, ECSValveState loxPressurant_, ECSValveState loxFlow_, ECSValveState loxPurge_, ECSValveState kerVent_, ECSValveState kerPressurant_, ECSValveState kerFlow_, ECSValveState kerPurge_):
            loxVent(loxVent_),
            loxPressurant(loxPressurant_),
            loxFlow(loxFlow_),
            loxPurge(loxPurge_),
            kerVent(kerVent_),
            kerPressurant(kerPressurant_),
            kerFlow(kerFlow_),
            kerPurge(kerPurge_){}
    CommandData() = default;
    CommandData(const SensorData &) = delete;
    CommandData &operator=(const SensorData &) = delete;
    ECSValveState loxVent = ECSValveState::INVALID;
    ECSValveState loxPressurant = ECSValveState::INVALID;
    ECSValveState loxFlow = ECSValveState::INVALID;
    ECSValveState loxPurge = ECSValveState::INVALID;
    ECSValveState kerVent = ECSValveState::INVALID;
    ECSValveState kerPressurant = ECSValveState::INVALID;
    ECSValveState kerFlow = ECSValveState::INVALID;
    ECSValveState kerPurge = ECSValveState::INVALID;
};

bool inline operator==(const CommandData& first, const CommandData second){
    return first.loxVent == second.loxVent
        and first.loxPressurant == second.loxPressurant
        and first.loxFlow == second.loxFlow
        and first.loxPurge == second.loxPurge
        and first.kerVent == second.kerVent
        and first.kerPressurant == second.kerPressurant
        and first.kerFlow == second.kerFlow
        and first.kerPurge == second.kerPurge;
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
