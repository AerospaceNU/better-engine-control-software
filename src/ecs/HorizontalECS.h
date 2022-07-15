//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#include "IECS.h"
#include "comm-boundary/ICommBoundary.h"
#include "utils-and-constants/ThreadQueue.h"
#include "utils-and-constants/ECSUtils.h"
#include <tuple>
#include <variant>
#include <chrono>
#include <queue>
#include "MessageStructs.h"

/**
 * Implementation of the IECS for the horizontal test stand
 *
 * Supports the ability to accept and return user commands, run automatic
 * sequences, and check for unexpected sensor values
 */
class HorizontalECS: public IECS{
public:
    HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, std::queue<std::variant<AbortCommand, StateCommand, OverrideCommand, SequenceCommand>> comQueue,
                  WatchDog& wDog, Sequencer& seq, ECSState& curState, ECSState& uniSafe);

    HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound,
                  WatchDog& wDog, Sequencer& seq, ECSState& curState, ECSState& uniSafe);

    void acceptSequence(ISequence& seq) override;
    void acceptStateTransition(ECSState& newState) override;
    void acceptOverrideCommand(CommandData commands) override;

    void stepECS() override;
    void acceptAbort() override;

protected:
    bool underAutoControl();
    void changeECSState(ECSState& state);
    void abort();

    ICommBoundary& networker;
    IPhysicalBoundary& boundary;


    //ThreadQueue<std::tuple<ECSCommand, std::variant<ISequence*, ECSState*, CommandData>>> commandQueue;
    // might want to consider making this a typedef? idk kinda long af
    ThreadQueue<std::variant<AbortCommand, StateCommand, OverrideCommand, SequenceCommand>> commandQueue;

    WatchDog& watchDog;
    Sequencer& sequencer;

    ECSState* fallbackState;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
