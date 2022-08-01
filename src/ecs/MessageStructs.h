//
// Created by kevin on 7/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H

#include "utils-and-constants/ECSState.h"
#include "sequencer/ISequence.h"
#include "utils-and-constants/CommandData.h"
#include "HorizontalECS.h"

#include "ECSCommand.h"


struct AbortCommand: public ECSCommand{
    void applyCommand(HorizontalECS& ecs) override {
        ecs.abort();
        ecs.networker.reportMessage("ECS has aborted!");
    }
};


struct StateCommand: public ECSCommand{
    explicit StateCommand(ECSState& newState):
        newState(newState)
    {}

    ECSState& newState;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.changeECSState(this->newState);
        //TODO: return message
    }
};

struct OverrideCommand: public ECSCommand{
    explicit OverrideCommand(const CommandData& data):
        newCommand(data)
    {}

    CommandData newCommand;

    void applyCommand(HorizontalECS& ecs) override {
        ecs.boundary.writeToBoundary(this->newCommand);
        //TODO: return message
    }
};

struct SequenceCommand: public ECSCommand{
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
