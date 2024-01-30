//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_STANDECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_STANDECS_H
#include "IECS.h"
#include "MessageStructs.h"

#include "comm-boundary/ICommBoundary.h"
#include "phys-boundary/IPhysicalBoundary.h"
#include "watchdog/IWatchDog.h"
#include "sequencer/Sequencer.h"

#include "utils/ThreadQueue.h"

#include <string>
#include <variant>


/**
 * Implementation of the IECS for the horizontal test stand
 *
 * Supports the ability to accept and return user commands, run automatic
 * sequencer, and check for unexpected sensor values.
 *
 * The overriden IECS methods ARE thread-safe to use
 */
class StandECS: public IECS{
public:
    StandECS(
           // ICommBoundary& net,
            IPhysicalBoundary& bound, IWatchDog& wDog, Sequencer& seq,
             const ECSState& curState,
             std::queue<std::variant<AbortCommand, AbortSequenceCommand>> specialQueue = {},
             std::queue<std::variant<StateCommand, OverrideCommand, StartSequenceCommand>> comQueue = {});

    // ICommBoundary should now be a global object and not passed into the ecs
    void setCommObject(ICommBoundary& newNetworker);
    ICommBoundary& getCommObject();

    StandECS(const StandECS& other) = delete;
    StandECS& operator=(StandECS other) = delete;

    /*
     * Thread safe
     */
    void acceptStartSequence(ISequence& seq) override;
    /*
     * Thread safe
     */
    void acceptStateTransition(ECSState newState) override;
    /*
     * Thread safe
     */
    void acceptOverrideCommand(CommandData commands) override;
    /*
     * Thread safe
     */
    void acceptAbortSequence() override;
    /*
     * Thread safe
     */
    void acceptAbort() override;

    /**
     * THIS METHOD IS NOT THREADSAFE, YOU CANNOT CALL
     * stepECS ON THE SAME StandECS OBJECT IN DIFFERENT THREADS
     *
     * This method will for each call:
     * - get sensor data
     * - send the data to watchdog and handle its results
     * - if there is a sequence running:
     *      - do that sequence
     * - else:
     *      - process commands in the queue
     *
     * - it will send messages to the comm boundary whenever necessary
     */
    void stepECS();

private:
    /**
     * Checks whether or not a sequence is currently running in the sequencer
     * @return true seq running, false otherwise
     */
    bool underAutoControl();

    /**
     * Helper method for changing states, will write to boundary, update redlines and fallback state
     * @param state cur state to change to
     */
    void changeECSState(ECSState& state) noexcept;

    /**
     * Helper method for aborting the ECS. Will stop any sequence running, and reset to fallback state
     */
    void abort();

    /**
     * Writes to stored boundary, catches possible exception from writing and sends message to comm
     * @param data data to write to bounday
     */
    void encapsulatedBoundaryWrite(CommandData& data) noexcept;

//    ICommBoundary& networker;
    IPhysicalBoundary& boundary;

    IWatchDog& watchDog;
    Sequencer& sequencer;

    std::string curState;

    CommandData fallbackState;

    ThreadQueue<std::variant<AbortCommand, AbortSequenceCommand>> specialQueue;
    ThreadQueue<std::variant<StateCommand, OverrideCommand, StartSequenceCommand>> commandQueue;

    /**
     * these allow the command design objects to access private data in the class
     * its kinda fucked up that we have to do this for each derived class, but
     * friendship isn't inherited, so "friend class IECSCommand" doesn't work
     */
    friend struct AbortCommand;
    friend struct AbortSequenceCommand;

    friend struct StateCommand;
    friend struct OverrideCommand;
    friend struct StartSequenceCommand;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_STANDECS_H
