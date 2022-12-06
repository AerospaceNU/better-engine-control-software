//
// Created by kevin on 6/15/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H

#include "utils/ECSState.h"

const extern ECSState ONLINE_SAFE;
const extern ECSState KER_FILL;
const extern ECSState KER_POST_FILL;
const extern ECSState LOX_FILL;
const extern ECSState LOX_POST_FILL;
const extern ECSState ALL_READY_TO_PRESSURIZE;
const extern ECSState ALL_PRESSURIZING;
const extern ECSState LOX_PRESSURIZING;
const extern ECSState KER_PRESSURIZING;
const extern ECSState ALL_FLOW;
const extern ECSState LOX_FLOW;
const extern ECSState KER_FLOW;
const extern ECSState LOX_GRAV_FLOW;
const extern ECSState LOX_ENGINE_PURGE;
const extern ECSState KER_ENGINE_PURGE;
const extern ECSState ALL_ENGINE_PURGE;
const extern ECSState PRESSURIZED_ALL_ENGINE_PURGE;
const extern ECSState LOX_TANK_PURGE;
const extern ECSState KER_TANK_PURGE;
const extern ECSState ALL_TANK_PURGE;
const extern ECSState LOX_FLUTTER_CLOSED;
const extern ECSState LOX_FLUTTER_OPEN;
const extern ECSState KER_FLUTTER_CLOSED;
const extern ECSState KER_FLUTTER_OPEN;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
