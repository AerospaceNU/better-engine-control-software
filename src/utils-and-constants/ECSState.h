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
    /*
     * All ECSStates are initialized on startup. If we ever need to create new
     * ECSStates during the runtime of the program, then we will need to revisit
     * all the places we store pointers/references to ECSStates to make sure they
     * stay valid
     */
    ECSState(std::string name, std::vector<IRedline*>& redlines, const CommandData& config, ECSState& failState);

    ECSState& operator=(ECSState other) = delete;

    std::string name;
    std::vector<IRedline*>& redlines;
    CommandData config;
    ECSState& failState;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
