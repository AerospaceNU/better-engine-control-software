#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H

#include "utils-and-constants/CommandData.h"
#include "utils-and-constants/SensorData.h"
#include "utils-and-constants/ECSState.h"
#include "sequencer/ISequence.h"

/**
 * An IECS is an abstraction for the main processor of the software. It has the ability
 * to accept new commands from either overrides or pre-configured states, as well as
 * apply these changes to the actual device, and report back to an overseer.
 */
class IECS {
public:
    /**
     * Runs the ECS for one step. Will process previously accepted commands
     * if ECS is not in automatic. Exact details implementation defined.
     */
    virtual void stepECS() = 0;

    /**
     * Accepts a command to transition to a specified ECS state
     * @param newState state to transition to
     */
    virtual void acceptStateTransition(ECSState& newState) = 0;

    /**
     * Accepts a command to transition to manual override state
     * @param commands commands representing the target configuration
     */
    virtual void acceptOverrideCommand(CommandData commands) = 0;


    /**
     * Accepts a command to switch to automatic control for this sequence
     * @param seq sequence to run
     */
    virtual void acceptSequence(ISequence& seq) = 0;

    /**
     * Emergency acceptAbort, will stop and clear all activites. Returning to
     * a safe state is implementation defined.
     */
    virtual void acceptAbort() = 0;

    /*
     * Other ideas for methods/commands (not strictly necessary rn)
     *  - toggle whether or not to ignore redline aborts
     *      - might be having occasionally fucked up sensor readings due to hardware, don't want
     *      the redlines to keep aborting in this case
     *
     *  - heartbeat command from comm boundary
     *      - or some way to tell ECS to kill itself if no operator connection
     *
     *  - get report of current total state
     *      - if the data on the operator side is desynced from the actual result, this would re-sync it
     */

    virtual ~IECS() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ECS_H
