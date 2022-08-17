//
// Created by kevin on 7/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H

#include <string>
#include "utils/ECSUtils.h"
#include "utils/ECSState.h"
#include "sequencer/sequences/ISequence.h"

/**
 * Function to return string presentation of a ECSValveState
 * @param state given state
 * @return string translation (ex. "OPEN" for ECSValveState::OPEN)
 */
std::string valveStateToString(ECSValveState state);

/**
 * Function to return ECSValveState enum from string
 * @param stateString input string
 * @return enum value (ex. ECSValveState::OPEN for "OPEN")
 * @throws exception if no match for given string, TODO
 */
ECSValveState stringToValveState(std::string stateString);

/**
 * Function to return ECSState from string
 * @param wantedState name of wanted ECSState
 * @return reference to ECSState
 * @throws exception if no match for given string, TODO
 */
ECSState& stringToECSState(std::string wantedState);

/**
 * Function to return ISequence from string
 * @param wantedSeq name of wanted sequence
 * @return  reference to desired sequence
 * @throws exception if no match for given string, TODO
 */
ISequence& stringToSequence(std::string wantedSeq);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
