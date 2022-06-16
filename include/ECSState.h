//
// Created by kevin on 5/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H

#include <string>
#include <vector>
#include "generic/IRedline.h"
#include "CommandData.h"

class ECSState{
public:
    ECSState(std::string name, const std::vector<const IRedline*>& redlines, CommandData* config, const ECSState& failState);

    const std::string name;
    const std::vector<const IRedline*>& redlines;
    const CommandData* config;
    const ECSState& failState;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
