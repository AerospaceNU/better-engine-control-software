//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#include "IECS.h"

#include "comm-boundary/ICommBoundary.h"
#include "phys-boundary/IPhysicalBoundary.h"
#include "watchdog/WatchDog.h"
#include "sequencer/Sequencer.h"

#include "utils/ThreadQueue.h"

#include <string>
#include <queue>
#include <memory>
#include "IECSCommand.h"
#include "IECSHighCommand.h"

#include "logger/Logger.h"

/**
 * Implementation of the IECS for the horizontal test stand
 *
 * Supports the ability to accept and return user commands, run automatic
 * sequencer, and check for unexpected sensor values.
 *
 * The overriden IECS methods are thread-safe to use
 */
class HorizontalECS: public IECS{
public:
    HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, WatchDog& wDog, Sequencer& seq, Logger& log,
                  ECSState& curState, ECSState& uniSafe,
                  std::queue<std::unique_ptr<IECSHighCommand>> specialQueue = {},
                  std::queue<std::unique_ptr<IECSCommand>> comQueue = {});


    HorizontalECS(const HorizontalECS& other) = delete;
    HorizontalECS& operator=(HorizontalECS other) = delete;


    void acceptStartSequence(ISequence& seq) override;
    void acceptStateTransition(ECSState& newState) override;
    void acceptOverrideCommand(CommandData commands) override;
    void acceptAbortSequence() override;
    void acceptAbort() override;

    /**
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

    ICommBoundary& networker;
    IPhysicalBoundary& boundary;

    WatchDog& watchDog;
    Sequencer& sequencer;
    Logger& logger;

    std::string curState;

    CommandData fallbackState;

    ThreadQueue<std::unique_ptr<IECSHighCommand>> specialQueue;
    ThreadQueue<std::unique_ptr<IECSCommand>> commandQueue;

    //these allow the command design objects to access private data in the class
    //its kinda fucked up that we have to do this for each derived class, but
    //friendship isn't inherited, so "friend class IECSCommand" doesn't work
    friend struct AbortCommand;
    friend struct AbortSequenceCommand;
    friend struct StateCommand;
    friend struct OverrideCommand;
    friend struct StartSequenceCommand;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
