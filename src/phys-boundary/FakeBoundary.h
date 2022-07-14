#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

#include "IPhysicalBoundary.h"

class FakeBoundary : public IPhysicalBoundary{
public:
    SensorData readFromBoundary() override;
    void writeToBoundary(CommandData& data) override;
private:
    SensorData curData;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

