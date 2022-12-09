#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H

#include "utils/CommandData.h"
#include "utils/SensorData.h"
#include "utils/ECSState.h"
#include "sequencer/sequences/ISequence.h"

/**
 * An IECS is an abstraction for the main processor of the software. It has the ability
 * to accept new commands from either overrides or pre-configured states, as well as
 * apply these changes to the actual device, and report back to an overseer.
 */
class IECS {
public:
    /**
     * Accepts a command to transition to a specified ECS state
     * @param newState state to transition to
     */
    virtual void acceptStateTransition(ECSState newState) = 0;

    /**
     * Accepts a command to transition to manual override state
     * @param commands commands representing the target configuration
     */
    virtual void acceptOverrideCommand(CommandData commands) = 0;


    /**
     * Accepts a command to switch to automatic control for this sequence
     * @param seq sequence to run
     */
    virtual void acceptStartSequence(ISequence& seq) = 0;

    /**
     * Accepts a command to abort the current sequence running
     */
    virtual void acceptAbortSequence() = 0;

    /**
     * Emergency acceptAbort, will stop and clear all activites. Returning to
     * a safe state is implementation defined.
     */
    virtual void acceptAbort() = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IECS() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H
