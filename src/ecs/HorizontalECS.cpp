//
// Created by kevin on 5/23/2022.
//

#include "HorizontalECS.h"
#include "MessageStructs.h"
#include "logger/Logger.h"
#include <queue>


HorizontalECS::HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, WatchDog& wDog, Sequencer& seq, Logger& log,
                             ECSState& cState, ECSState& uniSafe, std::queue<std::unique_ptr<IECSCommand>> comQueue) :
        networker(net),
        boundary(bound),
        watchDog(wDog),
        sequencer(seq),
        logger(log),

        curState(cState.name),
        fallbackState(&uniSafe),
        
        commandQueue(std::move(comQueue))
{}

void HorizontalECS::stepECS() {
    //TODO: if we call an abort, should we stop the rest of the method?

    //First part: get current readings from sensors
    SensorData curData = this->boundary.readFromBoundary();
    this->networker.reportSensorData(curData);
    this->logger.write_row(curData);
    //TODO: is there a place we gracefully shut down ECS? if so we should put the log csv closer there

    //Second part: run through redlines
    for (auto failedRedlinePair: this->watchDog.stepRedlines(curData)) {
        ECSRedLineResponse failedResponse = failedRedlinePair.first;
        IRedline *failedRedline = failedRedlinePair.second;

        //failedRedline->response;
        //failedRedline->errorMessage(curData);
        //TODO: process each failed redline in some way

        this->networker.reportRedlines(std::pair<ECSRedLineResponse, IRedline *>(failedResponse, failedRedline));
    }

    // Third part: run commands/sequencer
    // If we are not currently doing a sequence, we process user commands
    // Otherwise, the sequencer takes priority and we wait for it to be done before other overrides
    // TODO: make user aborts during a sequence possible
    if (!this->underAutoControl()) {
        while (this->commandQueue.size() > 0) {
            std::unique_ptr<IECSCommand> message = std::move(this->commandQueue.front());
            this->commandQueue.pop();

            message->applyCommand(*this);
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
    this->commandQueue.push(std::make_unique<StateCommand>(newState));
}

void HorizontalECS::acceptOverrideCommand(CommandData commands) {
    this->commandQueue.push(std::make_unique<OverrideCommand>(commands));
}

void HorizontalECS::acceptSequence(ISequence& seq) {
    this->commandQueue.push(std::make_unique<SequenceCommand>(seq));
}

void HorizontalECS::acceptAbort() {
    this->commandQueue.push(std::make_unique<AbortCommand>());
}


//PRIVATE FUNCTIONS
bool HorizontalECS::underAutoControl() {
    return this->sequencer.sequenceRunning();
}

void HorizontalECS::abort() {
    this->sequencer.abortSequence();

    //TODO: we are kinda fucked if this method fails. is there anything we can do software side?
    this->changeECSState(*this->fallbackState);
}

void HorizontalECS::changeECSState(ECSState &state) noexcept {
    try { // we SHOULD NOT use encapsulatedBoundaryWrite for the strong exception guarantee
        this->boundary.writeToBoundary(state.config);
        this->watchDog.updateRedlines(state.redlines);
        this->fallbackState = &state.failState;
        this->networker.reportState(state);
    }
    catch (EffectorException& e){
        this->networker.reportMessage(e.what());
    }
}

void HorizontalECS::encapsulatedBoundaryWrite(CommandData &data) noexcept {
    try{
        this->boundary.writeToBoundary(data);
    }
    catch (EffectorException& e){
        this->networker.reportMessage(e.what());
    }
}





