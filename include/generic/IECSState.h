//
// Created by kevin on 5/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H

#include <string>
#include <vector>
#include "IRedline.h"
#include "CommandData.h"

class IECSState{
public:
    virtual std::string getECSStateName() = 0;
    virtual std::vector<IRedline*> getRedlines() = 0;
    virtual CommandData* getCommandData() = 0;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
