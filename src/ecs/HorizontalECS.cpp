//
// Created by kevin on 5/23/2022.
//

#include "HorizontalECS.h"

#include <queue>



HorizontalECS::HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, std::queue<std::variant<AbortCommand, StateCommand, OverrideCommand, SequenceCommand>> comQueue,
                             WatchDog& wDog, Sequencer& seq, ECSState& curState, ECSState& uniSafe) :
        networker(net),
        boundary(bound),
        commandQueue(comQueue),
        watchDog(wDog),
        sequencer(seq),
        fallbackState(&uniSafe) {

    this->networker.acceptECS(*this);
}

HorizontalECS::HorizontalECS(ICommBoundary &net, IPhysicalBoundary &bound, WatchDog &wDog, Sequencer &seq,
                             ECSState &curState, ECSState &uniSafe) :
        HorizontalECS(net,
                      bound,
                      std::queue<std::variant<AbortCommand, StateCommand, OverrideCommand, SequenceCommand>>{},
                      wDog,
                      seq,
                      curState,
                      uniSafe)
{}

void HorizontalECS::stepECS() {
    //TODO: if we call an abort, should we stop the rest of the method?

    //First part: get current readings from sensors
    SensorData curData = this->boundary.readFromBoundary();
    this->networker.reportSensorData(curData);

    //Second part: run through redlines
    for (std::tuple<ECSRedLineResponse, IRedline *> failedRedlinePair: this->watchDog.stepRedlines(curData)) {
        ECSRedLineResponse failedResponse = std::get<0>(failedRedlinePair);
        IRedline *failedRedline = std::get<1>(failedRedlinePair);

        //failedRedline->response;
        //failedRedline->errorMessage(curData);
        //TODO: process each failed redline in some way

        this->networker.reportRedlines(std::tuple<ECSRedLineResponse, IRedline *>(failedResponse, failedRedline));
    }

    //Third part: run commands/sequences
    // If we are not currently doing a sequence, we process user commands
    // Otherwise, the sequencer takes priority and we wait for it to be done before other overrides
    // TODO: make user aborts during a sequence possible
    if (!this->underAutoControl()) {
        while (this->commandQueue.size() > 0) {
            auto message = this->commandQueue.front();
            this->commandQueue.pop();


            if (std::holds_alternative<AbortCommand>(message)) {
                this->abort();

                this->networker.reportMessage("ECS has aborted!");
            } else if (std::holds_alternative<StateCommand>(message)) {
                ECSState &newState = std::get<StateCommand>(message).newState;

                this->changeECSState(newState);

                //TODO: return message
            } else if (std::holds_alternative<OverrideCommand>(message)) {
                CommandData &newCommand = std::get<OverrideCommand>(message).newCommand;

                this->boundary.writeToBoundary(newCommand);

                //TODO: return message
            } else if (std::holds_alternative<SequenceCommand>(message)) {
                ISequence &newSeq = std::get<SequenceCommand>(message).newSequence;

                this->sequencer.startSequence(getTimeStamp(), newSeq);

                //TODO: return a message
            } else {
                //TODO, log and send a message back
            }
        }
    } else {
        ECSState *nextMove = this->sequencer.stepSequence(getTimeStamp());
        if (nextMove) {
            this->changeECSState(*nextMove);
        }
    }

    //TODO: parse another message back?
}


void HorizontalECS::acceptStateTransition(ECSState& newState) {
    this->commandQueue.push(StateCommand(newState));
}

void HorizontalECS::acceptOverrideCommand(CommandData commands) {
    this->commandQueue.push(OverrideCommand(commands));
}

void HorizontalECS::acceptSequence(ISequence& seq) {
    this->commandQueue.push(SequenceCommand(seq));
}

void HorizontalECS::acceptAbort() {
    this->commandQueue.push(AbortCommand());
}



bool HorizontalECS::underAutoControl() {
    return this->sequencer.sequenceRunning();
}

void HorizontalECS::abort() {
    this->sequencer.abortSequence();

    this->changeECSState(*this->fallbackState);
}

void HorizontalECS::changeECSState(ECSState &state) {
    this->boundary.writeToBoundary(state.config);
    this->watchDog.updateRedlines(state.redlines);

    this->fallbackState = &state.failState;
}





