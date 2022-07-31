//
// Created by kevin on 5/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H

#include <string>
#include <vector>
#include "watchdog/IRedline.h"
#include "utils-and-constants/CommandData.h"

/**
 * Represents a pre-defined state for the ECS to transition to
 */
class ECSState{
public:
    ECSState(std::string name, std::vector<IRedline*>& redlines, const CommandData& config, ECSState& failState);

    std::string name;
    std::vector<IRedline*>& redlines;
    CommandData config;
    ECSState& failState;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
