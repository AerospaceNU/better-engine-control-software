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
/**
 * An IECS is an abstraction for the main processor of the software. It has the ability
 * to accept new commands from either overrides or pre-configured states, as well as
 * apply these changes to the actual device, and report back to an overseer.
 */
class IECS {
public:
    /**
     * TODO
     */
    virtual void reportToBoundary() = 0;

    /**
     * Runs the ECS for one step. Exact details implementation defined.
     */
    virtual void stepECS() = 0;

    /**
     * Accepts a command to transition to a specified ECS state
     * @param newState state to transition to
     */
    virtual void acceptStateTransition(ECSState newState) = 0;

    /**
     * Accepts a command to transition to manual override state
     * @param commands commands representing the target configuration
     */
    virtual void acceptCommand(CommandData* commands) = 0;

    /**
     * Emergency abort, will stop and clear all activites. Returning to
     * a safe state is implementation defined.
     */
    virtual void abort() = 0;
};

#endif
