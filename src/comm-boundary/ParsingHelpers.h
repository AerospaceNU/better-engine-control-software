//
// Created by kevin on 7/17/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H

#include <string>
#include "utils/ECSUtils.h"
#include "utils/ECSState.h"
#include "sequencer/sequences/ISequence.h"
#include <stdexcept>

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
 * @throws std::invalid_argument if no match for given string
 */
ECSValveState stringToValveState(const std::string& stateString);

/**
 * Function to return ECSState from string
 * @param wantedState name of wanted ECSState
 * @return reference to ECSState
 * @throws std::invalid_argument if no match for given string
 */
const ECSState& stringToECSState(const std::string& wantedState);

/**
 * Function to return ISequence from string
 * @param wantedSeq name of wanted sequence
 * @return  reference to desired sequence
 * @throws std::invalid_argument if no match for given string
 */
ISequence& stringToSequence(const std::string& wantedSeq);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_PARSINGHELPERS_H
