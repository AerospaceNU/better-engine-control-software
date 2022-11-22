//
// Created by kevin on 7/17/2022.
//

#include "ParsingHelpers.h"
#include "constants/AllECSStates.h"
#include "sequencer/sequences/RelatTimedSequence.h"
#include <stdexcept>

std::string valveStateToString(ECSValveState state){
    switch (state){
        case ECSValveState::OPEN:
            return "OPEN";
        case ECSValveState::CLOSED:
            return "CLOSED";
        case ECSValveState::INVALID:
            return "INVALID";
    }
    return "INVALID";
}

ECSValveState stringToValveState(std::string stateString){
    if (stateString == "OPEN"){
        return ECSValveState::OPEN;
    }
    else if (stateString == "CLOSED"){
        return ECSValveState::CLOSED;
    }
    else{
        throw std::invalid_argument(R"(Must receive "OPEN" or "CLOSED")");
    }
}

ECSState& stringToECSState(std::string wantedState){
    if (wantedState == "ONLINE_SAFE_D") {
        return ONLINE_SAFE_D;
    }
    else if (wantedState == "KERO_FILL") {
        return KERO_FILL;
    }
    else if (wantedState == "KERO_FILLED") {
        return KERO_FILLED;
    }
    else if (wantedState == "LOX_FILL") {
        return LOX_FILL;
    }
    else if (wantedState == "LOX_FILLED") {
        return LOX_FILLED;
    }
    else if (wantedState == "ONLINE_SAFE") {
        return ONLINE_SAFE;
    }
    else if (wantedState == "READY_TO_PRESSURIZE") {
        return READY_TO_PRESSURIZE;
    }
    else if (wantedState == "PRESSURIZING") {
        return PRESSURIZING;
    }
    else if (wantedState == "FIRE") {
        return FIRE;
    }
    else if (wantedState == "ENGINE_PURGE") {
        return ENGINE_PURGE;
    }
    else if (wantedState == "TANK_PURGE") {
        return TANK_PURGE;
    }
    else {
        throw std::invalid_argument("String doesn't correspond to a state");
    }
}

ISequence& stringToSequence(std::string wantedSeq){
    throw std::invalid_argument("String doesn't correspond to a sequence");
}