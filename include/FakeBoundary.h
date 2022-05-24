#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

#include "generic/IPhysicalBoundary.h"

class FakeBoundary : public IPhysicalBoundary{
    SensorData* readFromBoundary();
    bool writeToBoundary(CommandData data);
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

