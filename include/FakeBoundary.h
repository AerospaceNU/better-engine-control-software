#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

#include "PhysicalBoundary.h"

class FakeBoundary : public PhysicalBoundary{
    SensorData* readFromBoundary();
    bool writeToBoundary(CommandData data);
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

