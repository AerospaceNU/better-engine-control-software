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

#include "utils-and-constants/ThreadQueue.h"

#include <queue>
#include <memory>
#include "ECSCommand.h"

/**
 * Implementation of the IECS for the horizontal test stand
 *
 * Supports the ability to accept and return user commands, run automatic
 * sequences, and check for unexpected sensor values
 */
class HorizontalECS: public IECS{
public:
    HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, std::queue<std::unique_ptr<ECSCommand>> comQueue,
                  WatchDog& wDog, Sequencer& seq, ECSState& curState, ECSState& uniSafe);

    HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound,
                  WatchDog& wDog, Sequencer& seq, ECSState& curState, ECSState& uniSafe);

    HorizontalECS(const HorizontalECS& other) = delete;
    HorizontalECS& operator=(HorizontalECS other) = delete;


    void acceptSequence(ISequence& seq) override;
    void acceptStateTransition(ECSState& newState) override;
    void acceptOverrideCommand(CommandData commands) override;
    void acceptAbort() override;

    /**
     * This method will for each call:
     * - get sensor data
     * - send the data to watchdog and handle its results
     * - if there is a sequence running:
     *      - do that sequence
     * - else:
     *      - process commands in the queue
     *      TODO currently doesn't process aborts if seq running, we want that.
     *
     * - it will send messages to the comm boundary whenever necessary
     */
    void stepECS() override;

private:
    bool underAutoControl();
    void changeECSState(ECSState& state);
    void abort();

    ICommBoundary& networker;
    IPhysicalBoundary& boundary;

    ThreadQueue<std::unique_ptr<ECSCommand>> commandQueue;

    WatchDog& watchDog;
    Sequencer& sequencer;

    //INVARIANT: fallbackState is never nullptr
    ECSState* fallbackState;

    friend class AbortCommand;
    friend class StateCommand;
    friend class OverrideCommand;
    friend class SequenceCommand;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
