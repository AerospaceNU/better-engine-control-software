//
// Created by kevin on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H

#include "Redline.h"
#include "SensorData.h"
#include "ValveRedline.h"
#include "IntWithinRedline.h"
#include "ECSUtils.h"
#include <vector>

std::vector<Redline*> LOX_FILL_REDLINES;

new IntWithinRedline("loxTankDucer",
                     [](SensorData* data){return data->loxTankDucer;},
                     0, 15);
new IntWithinRedline("kerTankDucer",
                    [](SensorData* data){return data->kerTankDucer;},
                    0, 15);

new IntWithinRedline("purgeDucer",
                    [](SensorData* data){return data->purgeDucer;},
                    0, 500);
new IntWithinRedline("loxInletDucer",
[](SensorData* data){return data->loxInletDucer;},
0, 15);
new IntWithinRedline("manifoldInletDucer",
[](SensorData* data){return data->manifoldInletDucer;},
0, 15);
new IntWithinRedline("kerInletDucer",
[](SensorData* data){return data->kerInletDucer;},
0, 15);
new IntWithinRedline("loxVenturi",
[](SensorData* data){return data->loxVenturi;},
0, 15);
new IntWithinRedline("kerVenturi",
[](SensorData* data){return data->kerVenturi;},
0, 15);

new IntWithinRedline("loadcell",
[](SensorData* data){return data->loadcell;},
0, 15);

new IntWithinRedline("loxTank1",
[](SensorData* data){return data->loxTank1;},
20, 30);
new IntWithinRedline("loxTank2",
[](SensorData* data){return data->loxTank2;},
20, 30);
new IntWithinRedline("loxTank3",
[](SensorData* data){return data->loxTank3;},
20, 30);
new IntWithinRedline("loxDripLine",
[](SensorData* data){return data->loxDripLine;},
20, 30);
new IntWithinRedline("outsideThroat",
[](SensorData* data){return data->outsideThroat;},
20, 30);
new IntWithinRedline("nozzle",
[](SensorData* data){return data->nozzle;},
20, 30);






#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINES_H
