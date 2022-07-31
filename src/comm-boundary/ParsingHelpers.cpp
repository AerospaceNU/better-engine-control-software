//
// Created by kevin on 7/17/2022.
//

#include "ParsingHelpers.h"
#include "utils-and-constants/HorizontalECSStates.h"
#include "sequencer/RelatTimedSequence.h"

std::string valveStateToString(ECSValveState state){
    switch (state){
        case ECSValveState::OPEN:
            return "OPEN";
        case ECSValveState::CLOSED:
            return "CLOSED";
        case ECSValveState::INVALID:
            return "INVALID";
    }
}

ECSValveState stringToValveState(std::string stateString){
    if (stateString == "OPEN"){
        return ECSValveState::OPEN;
    }
    else if (stateString == "CLOSED"){
        return ECSValveState::CLOSED;
    }
    else{
        //TODO: throw exception
        return ECSValveState::INVALID;
    }
}

ECSState& stringToECSState(std::string wantedState){
    return ONLINE_SAFE_D;
}

ISequence& stringToSequence(std::string wantedSeq){
    std::tuple<uint64_t, ECSState&> fuck(1, ONLINE_SAFE_D);
    std::vector<std::tuple<uint64_t, ECSState&>> fuckshit = {fuck, fuck, fuck};

    auto* seq = new RelatTimedSequence(&fuckshit);

    return *seq;
}