//
// Created by kevin on 5/23/2022.
//

#include "HorizontalECS.h"
#include "MessageStructs.h"
#include "logger/Logger.h"
#include <queue>


HorizontalECS::HorizontalECS(ICommBoundary& net, IPhysicalBoundary& bound, WatchDog& wDog, Sequencer& seq,
                             const ECSState& cState, const ECSState& uniSafe,
                             std::queue<std::unique_ptr<IECSHighCommand>> specQueue,
                             std::queue<std::unique_ptr<IECSCommand>> comQueue) :
        networker(net),
        boundary(bound),
        watchDog(wDog),
        sequencer(seq),

        curState(cState.getName()),
        fallbackState(uniSafe.getConfig()),

        specialQueue(std::move(specQueue)),
        commandQueue(std::move(comQueue))
{}

void HorizontalECS::stepECS() {
    //TODO: if we call an abort, should we stop the rest of the method?

    //First part: get current readings from sensors
    SensorData curData = this->boundary.readFromBoundary();
    this->networker.reportSensorData(curData, true);
    //TODO: is there a place we gracefully shut down ECS? if so we should put the log csv closer there

    //Second part: run through redlines
    auto redlinesReports = this->watchDog.stepRedlines(curData);

    for (auto& redlinePair: redlinesReports) {
        auto& [response, redline] = redlinePair;

        switch(response){
            case ECSRedLineResponse::ABORT:
                //after discussing auto aborts with prop, we can decide what actions we want to do
                //this->networker.reportMessage("Temp Message: Previous redline was an abort!");
                //this->abort();
                break;
            case ECSRedLineResponse::WARN:
                break;
            case ECSRedLineResponse::SAFE:
                //do nothing
                break;
        }
    }
    this->networker.reportRedlines(std::move(redlinesReports));

    // Third part: run commands/sequencer
    // our prioritys are (in order):
    // 1. special commands (sequence aborts/full aborts)
    // 2. other commands (overrides, state changes)
    // 3. automatic sequences
    if (this->specialQueue.size() > 0){
        while (this->specialQueue.size() > 0) {
            auto abortCom = std::move(this->specialQueue.front());
            this->specialQueue.pop();

            abortCom->applyHighCommand(*this);
        }
        return;
    }

    if (!this->underAutoControl()) {
        while (this->commandQueue.size() > 0) {
            auto message = std::move(this->commandQueue.front());
            this->commandQueue.pop();

            message->applyCommand(*this);
        }
    } else {
        auto possibleNextState = this->sequencer.stepSequence(getTimeStamp());
        if (possibleNextState) {
            this->changeECSState(possibleNextState.value());
        }
    }
}


void HorizontalECS::acceptStateTransition(ECSState newState) {
    this->commandQueue.push(std::make_unique<StateCommand>(std::move(newState)));
}

void HorizontalECS::acceptOverrideCommand(CommandData commands) {
    this->commandQueue.push(std::make_unique<OverrideCommand>(commands));
}

void HorizontalECS::acceptStartSequence(ISequence& seq) {
    this->commandQueue.push(std::make_unique<StartSequenceCommand>(seq));
}

void HorizontalECS::acceptAbortSequence() {
    this->specialQueue.push(std::make_unique<AbortSequenceCommand>());
}

void HorizontalECS::acceptAbort() {
    this->specialQueue.push(std::make_unique<AbortCommand>());
}


//PRIVATE FUNCTIONS
bool HorizontalECS::underAutoControl() {
    return this->sequencer.sequenceRunning();
}

void HorizontalECS::abort() {
    this->sequencer.abortSequence();

    //TODO: we are kinda fucked if this method fails. is there anything we can do software side?
    this->encapsulatedBoundaryWrite(this->fallbackState);
}

void HorizontalECS::changeECSState(ECSState &state) noexcept {
    try { // we SHOULD NOT use encapsulatedBoundaryWrite for the strong exception guarantee
        this->boundary.writeToBoundary(state.getConfig());
        this->watchDog.updateRedlines(state.getRedlines());
        this->fallbackState = state.getFailState();
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






