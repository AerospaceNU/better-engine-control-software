#include "MessageStructs.h"
#include "StandECS.h"

#include <utility>


void AbortCommand::applyHighCommand(StandECS& ecs) {
    ecs.abort();
    ecs.watchDog.updateRedlines({});
    ecs.networker.reportMessage("ECS has aborted!");
}



void AbortSequenceCommand::applyHighCommand(StandECS& ecs) {
    ecs.sequencer.abortSequence();
    ecs.networker.reportMessage("ECS aborted its sequence!");
}



StateCommand::StateCommand(ECSState newState_):
    newState(std::move(newState_))
{}

void StateCommand::applyCommand(StandECS& ecs) {
    ecs.changeECSState(this->newState);
}


OverrideCommand::OverrideCommand(const CommandData& data):
    newCommand(data)
{}

void OverrideCommand::applyCommand(StandECS& ecs) {
    ecs.encapsulatedBoundaryWrite(this->newCommand);
}



StartSequenceCommand::StartSequenceCommand(ISequence& newSeq):
    newSequence(newSeq)
{}

void StartSequenceCommand::applyCommand(StandECS& ecs)  {
    ecs.sequencer.startSequence(getTimeStamp(), this->newSequence);
    ecs.networker.reportMessage("New sequence started.");
}
