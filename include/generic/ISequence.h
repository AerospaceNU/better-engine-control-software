//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H

#include "utils-and-constants/ECSUtils.h"
#include "utils-and-constants/ECSState.h"
#include <stdint.h>

class ISequence{
    virtual ECSState stepSequence();
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISEQUENCE_H
