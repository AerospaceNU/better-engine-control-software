#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "watchdog/IRedline.h"
#include <vector>

/**
 * Constants representing the redlines used in the
 * horizontal test stand
 */
extern std::vector<IRedline*> ONLINE_SAFE_D_REDLINES;
extern std::vector<IRedline*> KERO_FILL_REDLINES;
extern std::vector<IRedline*> KERO_FILLED_REDLINES;
extern std::vector<IRedline*> LOX_FILL_REDLINES;
extern std::vector<IRedline*> LOX_FILLED_REDLINES;
extern std::vector<IRedline*> ONLINE_SAFE_REDLINES;
extern std::vector<IRedline*> READY_TO_PRESSURIZE_REDLINES;
extern std::vector<IRedline*> PRESSURIZING_REDLINES;
extern std::vector<IRedline*> FIRE_REDLINES;
extern std::vector<IRedline*> ENGINE_PURGE_REDLINES;
extern std::vector<IRedline*> TANK_PURGE_REDLINES;

//extern std::vector<std::reference_wrapper<IRedline>> ONLINE_SAFE_D;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
