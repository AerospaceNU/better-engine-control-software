//
// Created by kevin on 7/17/2022.
//

#include "ParsingHelpers.h"
#include "constants/AllECSStates.h"
#include <stdexcept>
#include "constants/AllSequences.h"

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

ECSValveState stringToValveState(const std::string& stateString){
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

const ECSState& stringToECSState(const std::string& wantedState){
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
    else if (wantedState == "ALL_READY_TO_PRESSURIZE") {
        return ALL_READY_TO_PRESSURIZE;
    }
    else if (wantedState == "ALL_PRESSURIZING") {
        return ALL_PRESSURIZING;
    }
    else if (wantedState == "ALL_FLOW_closed") {
        return ALL_FLOW_closed;
    }
    else if (wantedState == "ALL_FLOW_open") {
        return ALL_FLOW_open;
    }
    else if (wantedState == "KERO_FLOW_closed") {
        return KERO_FLOW_closed;
    }
    else if (wantedState == "KERO_FLOW_open") {
        return KERO_FLOW_open;
    }
    else {
        throw std::invalid_argument("String doesn't correspond to a state");
    }
}

ISequence& stringToSequence([[maybe_unused]] const std::string& wantedSeq){
    if (wantedSeq == "ALL_FLOW"){
        return ALL_FLOW;
    }
    else if (wantedSeq == "KERO_FLOW"){
        return KERO_FLOW;
    }
    else if (wantedSeq == "FIRE_3_SECONDS"){
        return FIRE_3_SECONDS;
    }
    else{
        throw std::invalid_argument("String doesn't correspond to a sequence");
    }
}
