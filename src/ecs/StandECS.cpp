//
// Created by kevin on 5/23/2022.
//

#include "StandECS.h"
#include "MessageStructs.h"
#include "logger/Logger.h"
#include <queue>


StandECS::StandECS(ICommBoundary& net, IPhysicalBoundary& bound, IWatchDog& wDog, Sequencer& seq,
                   const ECSState& cState,
                   std::queue<std::unique_ptr<IECSHighCommand>> specQueue,
                   std::queue<std::unique_ptr<IECSCommand>> comQueue) :
        networker(net),
        boundary(bound),
        watchDog(wDog),
        sequencer(seq),

        curState(cState.getName()),
        fallbackState(cState.getFailState()),

        specialQueue(std::move(specQueue)),
        commandQueue(std::move(comQueue))
{}

//PUBLIC METHODS
/*
 * These overriden methods that start with "accept..." MUST be thread-safe
 *
 * If you don't know what thread-safety is, google and stack overflow are
 * your best friends
 *
 * But what it means for these functions is that we cannot call any methods that
 * are not thread-safe in these functions. For example, you cannot call readFromBoundary()
 * on the inner IPhysicalBoundary bc it is not thread-safe. You cannot directly read or write
 * to any of the fields in this object UNLESS IT IS THREAD-SAFE
 *
 * We achieve thread-safety with a pattern called message-passing (google once again will be
 * your best friend). In short, we have queues that we can push and pop from that ARE thread-safe
 *
 * Effectively, the only things you can do in these functions is push values to these queue.
 *
 * FYI: this can be changed later in the code, but do not POP from these queues either. While they
 * are thread-safe as mentioned, it will fuck up some assumptions we make in the implementation of
 * stepECS(), which is that the queues are single consumer (again, google is bestie)
 */
void StandECS::acceptStateTransition(ECSState newState) {
    this->commandQueue.push(std::make_unique<StateCommand>(std::move(newState)));
}

void StandECS::acceptOverrideCommand(CommandData commands) {
    this->commandQueue.push(std::make_unique<OverrideCommand>(commands));
}

void StandECS::acceptStartSequence(ISequence& seq) {
    this->commandQueue.push(std::make_unique<StartSequenceCommand>(seq));
}

void StandECS::acceptAbortSequence() {
    this->specialQueue.push(std::make_unique<AbortSequenceCommand>());
}

void StandECS::acceptAbort() {
    this->specialQueue.push(std::make_unique<AbortCommand>());
}

//PUBLIC, BUT NOT THREADSAFE
void StandECS::stepECS() {
    //TODO: if we call an abort, should we stop the rest of the method?

    //First part: get current readings from sensors
    SensorData curData = this->boundary.readFromBoundary();
    this->networker.reportSensorData(curData, true);

    //Second part: run through redlines
    auto redlinesReports = this->watchDog.stepRedlines(curData);

    for (auto& packet: redlinesReports) {
        switch(packet.response){
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
        //clear accumulated regular command queue, ignoring the commands completely
        while (this->commandQueue.size() > 0) {
            this->commandQueue.pop();
        }

        auto possibleNextState = this->sequencer.stepSequence(getTimeStamp());
        if (possibleNextState) {
            this->changeECSState(possibleNextState.value());
        }
    }
}



//PRIVATE FUNCTIONS, NONE OF THESE ARE THREAD-SAFE
bool StandECS::underAutoControl() {
    return this->sequencer.sequenceRunning();
}

void StandECS::abort() {
    this->sequencer.abortSequence();

    //TODO: we are kinda fucked if this method fails. is there anything we can do software side?
    this->encapsulatedBoundaryWrite(this->fallbackState);
}

void StandECS::changeECSState(ECSState &state) noexcept {
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

void StandECS::encapsulatedBoundaryWrite(CommandData &data) noexcept {
    try{
        this->boundary.writeToBoundary(data);
    }
    catch (EffectorException& e){
        this->networker.reportMessage(e.what());
    }
}






