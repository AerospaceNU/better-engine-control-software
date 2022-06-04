#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "ValveRedline.h"
#include "IntWithinRedline.h"
#include <vector>

//extern const std::vector<const IRedline*> ONLINE_SAFE_D;

extern const std::vector<const IRedline*> ONLINE_SAFE_D;
extern const std::vector<const IRedline*> KERO_FILL;
extern const std::vector<const IRedline*> KERO_FILLED;
extern const std::vector<const IRedline*> LOX_FILL;
extern const std::vector<const IRedline*> LOX_FILLED;
extern const std::vector<const IRedline*> ONLINE_SAFE;
extern const std::vector<const IRedline*> READY_TO_PRESSURIZE;
extern const std::vector<const IRedline*> PRESSURIZING;
extern const std::vector<const IRedline*> FIRE;
extern const std::vector<const IRedline*> ENGINE_PURGE;
extern const std::vector<const IRedline*> TANK_PURGE;

//extern const std::vector<const std::reference_wrapper<IRedline>> ONLINE_SAFE_D;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
