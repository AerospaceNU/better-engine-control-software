//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_HORIZONTALECS_H
#include "generic/IECS.h"
#include "generic/ICommBoundary.h"
#include <chrono>
#include <queue>

class HorizontalECS: public IECS{
public:
    HorizontalECS(ICommBoundary* net, IPhysicalBoundary* bound, std::queue<CommandData*> comQueue,
                  WatchDog* wDog, Sequencer* seq, ECSState* curState, ECSState* uniSafe);
    //HorizontalECS(ICommBoundary* net, IPhysicalBoundary* bound, WatchDog* wDog);

    void reportToBoundary() override;
    void stepECS() override;
    void acceptStateTransition(ECSState newState) override;
    void acceptCommand(CommandData* commands) override;
    void abort() override;

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
