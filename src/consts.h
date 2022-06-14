//
// Created by Jack Hester on 6/13/22.
//
#include <string> //TODO: hmmm maybe we can avoid this later

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H

const std::string csvColNames[19] = {"time","state","loxInletDucer","kerInletDucer","purgeDucer",
                                  "kerPintleDucer", "loxTankDucer", "kerTankDucer", "pneumaticDucer",
                                  "loxN2Ducer","kerN2Ducer","loxVenturi", "kerVenturi",
                                  "manifoldInletThermo","manifoldOutletThermo","tank1Thermo","tank2Thermo",
                                  "tank3Thermo", "loadCell"}; //TODO: add valve states

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H
