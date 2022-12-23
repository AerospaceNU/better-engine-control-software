//
// Created by kevin on 12/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_OUTGOINGJSONPARSERS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_OUTGOINGJSONPARSERS_H

#include <json.hpp>
#include "watchdog/redlines/RedlineResponsePacket.h"
#include "utils/SensorData.h"
#include "utils/ECSState.h"

using json = nlohmann::json;

/**
 * Returns JSON object describing an ecs state transition on the ECS, for
 * the operator side GUI to get and parse
 *
 * This function will also record the current time
 *
 * @param curState state to report back
 * @return json formatted according to specification in examples folder
 */
json parseECSState(ECSState &curState);

/**
 * Returns JSON object describing a set of redlines ran by the watchdog on the ECS, for
 * the operator side GUI to get and parse
 *
 * This function will also record the current time
 *
 * @param redlineReports vector of redline results
 * @return json formatted according to specification in examples folder
 */
json parseRedlines(const std::vector<RedlineResponsePacket>& redlineReports);

/**
 * Returns JSON object describing a SensorData obtained from the ECS, for
 * the operator side GUI to get and parse
 *
 * This function will also record the current time
 *
 * @param data data
 * @param isCalibrated whether or not this data is calibrated or uncalibrated
 * @return json formatted according to specification in examples folder
 */
json parseSensorData(const SensorData& data, bool isCalibrated);

/**
 * Returns JSON object describing a general message to the operator side GUI to get and parse
 *
 * This function will also record the current time
 *
 * @param message string
 * @return json formatted according to specification in examples folder
 */
json parseMessage(const std::string& message);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_OUTGOINGJSONPARSERS_H
