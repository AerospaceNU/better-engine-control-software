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
    if (wantedState == "ONLINE_SAFE") {
        return ONLINE_SAFE;
    }
    else if (wantedState == "KER_FILL") {
        return KER_FILL;
    }
    else if (wantedState == "KER_POST_FILL") {
        return KER_POST_FILL;
    }
    else if (wantedState == "LOX_FILL") {
        return LOX_FILL;
    }
    else if (wantedState == "LOX_POST_FILL") {
        return LOX_POST_FILL;
    }
    else if (wantedState == "ALL_READY_TO_PRESSURIZE") {
        return ALL_READY_TO_PRESSURIZE;
    }
    else if (wantedState == "ALL_PRESSURIZING") {
        return ALL_PRESSURIZING;
    }
    else if (wantedState == "LOX_PRESSURIZING") {
        return LOX_PRESSURIZING;
    }
    else if (wantedState == "KER_PRESSURIZING") {
        return KER_PRESSURIZING;
    }
    else if (wantedState == "ALL_FLOW") {
        return ALL_FLOW;
    }
    else if (wantedState == "LOX_FLOW") {
        return LOX_FLOW;
    }
    else if (wantedState == "KER_FLOW") {
        return KER_FLOW;
    }
    else if (wantedState == "LOX_GRAV_FLOW") {
        return LOX_GRAV_FLOW;
    }
    else if (wantedState == "LOX_ENGINE_PURGE") {
        return LOX_ENGINE_PURGE;
    }
    else if (wantedState == "KER_ENGINE_PURGE") {
        return KER_ENGINE_PURGE;
    }
    else if (wantedState == "ALL_ENGINE_PURGE") {
        return ALL_ENGINE_PURGE;
    }
    else if (wantedState == "PRESSURIZED_ALL_ENGINE_PURGE") {
        return PRESSURIZED_ALL_ENGINE_PURGE;
    }
    else if (wantedState == "LOX_TANK_PURGE") {
        return LOX_TANK_PURGE;
    }
    else if (wantedState == "KER_TANK_PURGE") {
        return KER_TANK_PURGE;
    }
    else if (wantedState == "ALL_TANK_PURGE") {
        return ALL_TANK_PURGE;
    }
    else if (wantedState == "LOX_FLUTTER_CLOSED") {
        return LOX_FLUTTER_CLOSED;
    }
    else if (wantedState == "LOX_FLUTTER_OPEN") {
        return LOX_FLUTTER_OPEN;
    }
    else if (wantedState == "KER_FLUTTER_CLOSED") {
        return KER_FLUTTER_CLOSED;
    }
    else if (wantedState == "KER_FLUTTER_OPEN") {
        return KER_FLUTTER_OPEN;
    }
    else {
        throw std::invalid_argument("String doesn't correspond to a state");
    }
}

ISequence& stringToSequence(const std::string& wantedSeq){
    if (wantedSeq == "LOX_VENT_FLUTTER_x5") {
        return LOX_VENT_FLUTTER_x5;
    }
    else if (wantedSeq == "KER_VENT_FLUTTER_x5") {
        return KER_VENT_FLUTTER_x5;
    }
    else if (wantedSeq == "FIRE_3s") {
        return FIRE_3s;
    }
    else if (wantedSeq == "FIRE_15s") {
        return FIRE_15s;
    }
    else if (wantedSeq == "PURGE_ABORT") {
        return PURGE_ABORT;
    }
    else if (wantedSeq == "NO_PURGE_ABORT") {
        return NO_PURGE_ABORT;
    }
    else if (wantedSeq == "ONLINE_SAFE_ABORT") {
        return ONLINE_SAFE_ABORT;
    } else {
        throw std::invalid_argument("String doesn't correspond to a sequence");
    }

}