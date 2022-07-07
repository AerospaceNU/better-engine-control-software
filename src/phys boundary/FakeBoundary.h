#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

#include "IPhysicalBoundary.h"

class FakeBoundary : public IPhysicalBoundary{
    SensorData readFromBoundary() override;
    bool writeToBoundary(CommandData data) override;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

