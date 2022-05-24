//
// Created by kevin on 5/23/2022.
//

#include "HorizontalECS.h"


HorizontalECS::HorizontalECS(ICommBoundary *net, IPhysicalBoundary* bound, std::queue<CommandData *> comQueue,
                             WatchDog *wDog, Sequencer *seq, ECSState uniSafe) :
        networker(net),
        commandQueue(comQueue),
        watchDog(wDog),
        sequencer(seq),
        universalSafe(uniSafe) {}

HorizontalECS::HorizontalECS(ICommBoundary *net, IPhysicalBoundary *bound, WatchDog *wDog) {
    HorizontalECS(net, bound, *new std::queue<CommandData *>(), wDog, new Sequencer(), ONLINE_SAFE);
}

void HorizontalECS::stepECS() {
    SensorData* curData = this->boundary->readFromBoundary();

    for(IRedline* failedRedline: this->watchDog->stepRedlines(curData)){
        //failedRedline->response;
        //failedRedline->errorMessage(curData);
        //TODO: process each failed redline in some way
    }

    if(!this->underAutoControl()){
        while(!this->commandQueue.empty()){
            this->boundary->writeToBoundary(this->commandQueue.front());
            this->commandQueue.pop();
        }
    }
    else{
        ECSState nextMove = this->sequencer->stepSequence(this->getTimeStamp());
        if(nextMove != NULL){
            //TODO: turn ECSState in command data and write to boundary
        }
    }

    //TODO: parse another message back?
}

uint64_t HorizontalECS::getTimeStamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

void HorizontalECS::acceptCommand(CommandData *commands) {
    this->commandQueue.push(commands);
}

bool HorizontalECS::underAutoControl() {
    return this->sequencer->sequenceRunning();
}

void HorizontalECS::abort() {
    //TODO: kill sequence
    //TODO: turn universalSafe in command data and write to boundary
    //send abort messages
}




