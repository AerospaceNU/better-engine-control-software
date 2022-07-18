//
// Created by kevin on 7/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H

#include <string>
#include "utils-and-constants/ECSUtils.h"
#include "utils-and-constants/ECSState.h"
#include "sequencer/ISequence.h"

std::string valveStateToString(ECSValveState state);

ECSValveState stringToValveState(std::string stateString);

ECSState& stringToECSState(std::string wantedState);

ISequence& stringToSequence(std::string wantedSeq);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
