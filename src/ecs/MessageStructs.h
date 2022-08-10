//
// Created by kevin on 7/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H

#include "utils-and-constants/ECSState.h"
#include "sequencer/sequences/ISequence.h"
#include "utils-and-constants/CommandData.h"
#include "HorizontalECS.h"

#include "IECSCommand.h"


struct AbortCommand: public IECSCommand{
    void applyCommand(HorizontalECS& ecs) override {
        ecs.abort();
        ecs.networker.reportMessage("ECS has aborted!");
    }
};


struct StateCommand: public IECSCommand{
    explicit StateCommand(ECSState& newState):
        newState(newState)
    {}

    ECSState& newState;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.changeECSState(this->newState);
        //TODO: return message
    }
};

struct OverrideCommand: public IECSCommand{
    explicit OverrideCommand(const CommandData& data):
        newCommand(data)
    {}

    CommandData newCommand;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.encapsulatedBoundaryWrite(this->newCommand);
        //TODO: return message
    }
};

struct SequenceCommand: public IECSCommand{
    explicit SequenceCommand(ISequence& newSeq):
        newSequence(newSeq)
    {}

    ISequence& newSequence;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.sequencer.startSequence(getTimeStamp(), this->newSequence);
        //TODO: return message
    }
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
