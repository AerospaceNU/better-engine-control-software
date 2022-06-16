#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "ValveRedline.h"
#include "IntWithinRedline.h"
#include <vector>

//extern const std::vector<const IRedline*> ONLINE_SAFE_D;

extern const std::vector<const IRedline*> ONLINE_SAFE_D_REDLINES;
extern const std::vector<const IRedline*> KERO_FILL_REDLINES;
extern const std::vector<const IRedline*> KERO_FILLED_REDLINES;
extern const std::vector<const IRedline*> LOX_FILL_REDLINES;
extern const std::vector<const IRedline*> LOX_FILLED_REDLINES;
extern const std::vector<const IRedline*> ONLINE_SAFE_REDLINES;
extern const std::vector<const IRedline*> READY_TO_PRESSURIZE_REDLINES;
extern const std::vector<const IRedline*> PRESSURIZING_REDLINES;
extern const std::vector<const IRedline*> FIRE_REDLINES;
extern const std::vector<const IRedline*> ENGINE_PURGE_REDLINES;
extern const std::vector<const IRedline*> TANK_PURGE_REDLINES;

//extern const std::vector<const std::reference_wrapper<IRedline>> ONLINE_SAFE_D;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
