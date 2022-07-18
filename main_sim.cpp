/**
* This file is the main file for building a complete ecs on regular computers, with a simulated CommBoundary
*/
#include "ecs/HorizontalECS.h"
#include "comm-boundary/ECSNetworker.h"
#include "phys-boundary/FakeBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/WatchDog.h"
#include "utils-and-constants/HorizontalECSStates.h"

int main(){
    ECSNetworker networker;

    FakeBoundary boundary;

    WatchDog watchDog;

    Sequencer sequencer;

    HorizontalECS ecs(networker, boundary, watchDog, sequencer, ONLINE_SAFE_D, ONLINE_SAFE_D);

    return 0;
}
