#ifndef ECS_H
#define ECS_H

#include "CommandData.h"
#include "SensorData.h"
#include "ICommBoundary.h"
#include "IPhysicalBoundary.h"
#include "WatchDog.h"
#include "Sequencer.h"

class IECS {
public:
    virtual void reportToBoundary() = 0;
    virtual void stepECS() = 0;
    virtual void acceptCommand(CommandData* commands) = 0;
};

#endif
