//
// Created by kevin on 6/15/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H

#include "utils/ECSState.h"

const extern ECSState ONLINE_SAFE_D;
const extern ECSState KERO_FILL;
const extern ECSState KERO_FILLED;
const extern ECSState LOX_FILL;
const extern ECSState LOX_FILLED;
const extern ECSState ALL_READY_TO_PRESSURIZE;
const extern ECSState ALL_PRESSURIZING;
const extern ECSState ALL_FLOW_closed;
const extern ECSState ALL_FLOW_open;
const extern ECSState KERO_FLOW_closed;
const extern ECSState KERO_FLOW_open;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
