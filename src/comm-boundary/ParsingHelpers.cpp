//
// Created by kevin on 7/17/2022.
//

#include "ParsingHelpers.h"
#include "constants/HorizontalECSStates.h"
#include "sequencer/sequences/RelatTimedSequence.h"

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

//TODO: implement
ECSState& stringToECSState(std::string wantedState){
    return ONLINE_SAFE_D;
}

//TODO: implement
ISequence& stringToSequence(std::string wantedSeq){
    std::pair<uint64_t, ECSState&> fuck(1, ONLINE_SAFE_D);
    std::vector<std::pair<uint64_t, ECSState&>> fuckshit = {fuck, fuck, fuck};

    auto* seq = new RelatTimedSequence(fuckshit);

    return *seq;
}