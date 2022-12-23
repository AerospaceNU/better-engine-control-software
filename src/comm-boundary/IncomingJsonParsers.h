//
// Created by kevin on 12/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INCOMINGJSONPARSERS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INCOMINGJSONPARSERS_H

#include <json.hpp>
#include "ecs/IECS.h"

using json = nlohmann::json;

/**
 * Parses input json for ordering a start sequence command for an IECS
 * @param command json command to read from
 * @param ecs ecs to call on
 * @throws std::invalid_argument if JSON format is off
 */
void parseStartSequenceCommand(const json& command, IECS& ecs);

/**
 * Parses input json for ordering an abort sequence command for an IECS
 * @param command json command to read from
 * @param ecs ecs to call on
 * @throws std::invalid_argument if JSON format is off
 */
void parseAbortSequenceCommand(const json& command, IECS& ecs);

/**
 * Parses input json for ordering a custom valve configuration command for an IECS
 * @param command json command to read from
 * @param ecs ecs to call on
 * @throws std::invalid_argument if JSON format is off
 */
void parseOverrideCommand(const json& command, IECS& ecs);

/**
 * Parses input json for ordering a state transition command for an IECS
 * @param command json command to read from
 * @param ecs ecs to call on
 * @throws std::invalid_argument if JSON format is off
 */
void parseStateCommand(const json& command, IECS& ecs);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INCOMINGJSONPARSERS_H
