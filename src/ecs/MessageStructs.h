//
// Created by kevin on 7/14/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H

#include "utils-and-constants/ECSState.h"
#include "sequencer/ISequence.h"
#include "utils-and-constants/CommandData.h"

struct AbortCommand{

};

struct StateCommand{
    explicit StateCommand(ECSState& newState):
        newState(newState)
    {}

    ECSState& newState;
};

struct OverrideCommand{
    explicit OverrideCommand(const CommandData& data):
        newCommand(data)
    {}

    CommandData newCommand;
};

struct SequenceCommand{
    explicit SequenceCommand(ISequence* newSeq):
        newSequence(newSeq)
    {}

    ISequence* newSequence;
};

// currently unused, if we don't want to use <variant>, we can use this with an enum tag
union tempECSCommand{
    AbortCommand abort;
    StateCommand state;
    OverrideCommand override;
    SequenceCommand sequence;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_MESSAGESTRUCTS_H
