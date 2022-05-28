#ifndef ECS_H
#define ECS_H

#include "CommandData.h"
#include "SensorData.h"
#include "ICommBoundary.h"
#include "IPhysicalBoundary.h"
#include "WatchDog.h"
#include "Sequencer.h"

/*
 * Commands to ECS include:
 *  sending an ECS state
 *  sending a patch of command data
 *      these two have to be diff because we want to store the current ECSState in the ECS
 *      sending command data is manual override, aka unknown
 */
class IECS {
public:
    virtual void reportToBoundary() = 0;
    virtual void stepECS() = 0;
    virtual void acceptStateTransition(ECSState newState) = 0;
    virtual void acceptCommand(CommandData* commands) = 0;
    virtual void abort() = 0;
};

#endif
