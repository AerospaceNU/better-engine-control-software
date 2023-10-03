//
// Created by kevin on 7/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H

#include "IECSCommand.h"
#include "IECSHighCommand.h"

#include "utils/ECSState.h"
#include "sequencer/sequences/ISequence.h"
#include "utils/CommandData.h"

struct AbortCommand: public IECSHighCommand{
    void applyHighCommand(StandECS& ecs) override;
};

struct AbortSequenceCommand: public IECSHighCommand{
    void applyHighCommand(StandECS& ecs) override;
};

struct StateCommand: public IECSCommand{
    explicit StateCommand(ECSState newState_);

    ECSState newState;

    void applyCommand(StandECS& ecs) override;
};

struct OverrideCommand: public IECSCommand{
    explicit OverrideCommand(const CommandData& data);

    CommandData newCommand;

    void applyCommand(StandECS& ecs) override;
};

struct StartSequenceCommand: public IECSCommand{
    explicit StartSequenceCommand(ISequence& newSeq);

    ISequence& newSequence;

    void applyCommand(StandECS& ecs) override;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
