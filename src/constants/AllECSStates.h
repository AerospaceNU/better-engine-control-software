//
// Created by kevin on 6/15/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H

#include "utils/ECSState.h"

const extern ECSState ONLINE_SAFE_D;
const extern ECSState KERO_FILL;
const extern ECSState KERO_POST_FILL;
const extern ECSState LOX_FILL;
const extern ECSState LOX_POST_FILL;
const extern ECSState ALL_READY_TO_PRESSURIZE;
const extern ECSState ALL_PRESSURIZING;
const extern ECSState ALL_FLOW_closed;
const extern ECSState ALL_FLOW_open;
const extern ECSState KERO_FLOW_closed;
const extern ECSState KERO_FLOW_open;

const extern ECSState LOX_TANK_PURGE; //added hotfire 4-25
const extern ECSState KERO_TANK_PURGE; //added hotfire 4-25
const extern ECSState ALL_TANK_PURGE; //added hotfire 4-25
const extern ECSState LOX_FLUTTER_OPEN; //added hotfire 4-25
const extern ECSState LOX_FLUTTER_CLOSED; //added hotfire 4-25
const extern ECSState KERO_FLUTTER_OPEN; //added hotfire 4-25
const extern ECSState KERO_FLUTTER_CLOSED; //added hotfire 4-25


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ALLECSSTATES_H
