//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#include "IECS.h"
#include "comm-boundary/ICommBoundary.h"
#include <chrono>
#include <queue>

/**
 * Implementation of the IECS for the horizontal test stand
 *
 * Supports the ability to accept and return user commands, run automatic
 * sequences, and check for unexpected sensor values
 */
class HorizontalECS: public IECS{
public:
    HorizontalECS(ICommBoundary* net, IPhysicalBoundary* bound, std::queue<CommandData*> comQueue,
                  WatchDog* wDog, Sequencer* seq, ECSState* curState, ECSState* uniSafe);
    //HorizontalECS(ICommBoundary* net, IPhysicalBoundary* bound, WatchDog* wDog);

    void acceptSequence(ISequence* seq) override;
    void stepECS() override;
    void acceptStateTransition(ECSState& newState) override;
    void acceptCommand(CommandData commands) override;
    void abort() override;

    //void acceptSequence(ISequence seq);

protected:
    void acceptECSStateandCommand(ECSState& newState, CommandData* commands);
    bool underAutoControl();

    ICommBoundary* networker;
    IPhysicalBoundary* boundary;
    std::queue<CommandData*> commandQueue;

    WatchDog* watchDog;
    Sequencer* sequencer;

    ECSState* currentState;
    ECSState* universalSafe;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
