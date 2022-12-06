//
// Created by kevin on 7/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H

#include <utility>

#include "utils/ECSState.h"
#include "sequencer/sequences/ISequence.h"
#include "utils/CommandData.h"
#include "HorizontalECS.h"

#include "IECSCommand.h"
#include "IECSHighCommand.h"


struct AbortCommand: public IECSHighCommand{
    void applyHighCommand(HorizontalECS& ecs) override {
        ecs.abort();
        ecs.networker.reportMessage("ECS has aborted!");
    }
};

struct AbortSequenceCommand: public IECSHighCommand{
    void applyHighCommand(HorizontalECS& ecs) override {
        ecs.sequencer.abortSequence();
        ecs.networker.reportMessage("ECS aborted its sequence!");
    }
};


struct StateCommand: public IECSCommand{
    explicit StateCommand(ECSState newState_):
        newState(std::move(newState_))
    {}
    ECSState newState;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.changeECSState(this->newState);
    }
};

struct OverrideCommand: public IECSCommand{
    explicit OverrideCommand(const CommandData& data):
        newCommand(data)
    {}

    CommandData newCommand;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.encapsulatedBoundaryWrite(this->newCommand);
    }
};

struct StartSequenceCommand: public IECSCommand{
    explicit StartSequenceCommand(ISequence& newSeq):
        newSequence(newSeq)
    {}

    ISequence& newSequence;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.sequencer.startSequence(getTimeStamp(), this->newSequence);
        ecs.networker.reportMessage("New sequence started.");
    }
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
