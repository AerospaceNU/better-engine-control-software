//
// Created by kevin on 5/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H

#include "utils/CommandData.h"
#include <vector>
#include <utility>
#include "watchdog/redlines/IRedline.h"

#include "utils/SensorData.h"
#include "utils/ECSState.h"
#include "watchdog/redlines/RedlineResponsePacket.h"

/**
 * An ICommBoundary is an abstraction for a object for communication to a controller/operator.
 * When its functions are called, the object will take the inputted data and transmit messages
 * back using it.
 */
class ICommBoundary{
public:
    /**
     * Reports a state change
     * @param curState the state transitioned to
     */
    virtual void reportState(ECSState& curState) = 0;

    /**
     * Reports list of redline results back to operator
     * @param redlineReports list of redline response data packets
     */
    virtual void reportRedlines(std::vector<RedlineResponsePacket> redlineReports) = 0;

    /**
     * Reports the data back to the operator
     * @param data data from sensors
     * @param isCalibrated bool signalling whether the passed in data is calibrated or not
     */
    virtual void reportSensorData(SensorData data, bool isCalibrated) = 0;

    /**
     * General purpose method using for sending a specific string to operators.
     *
     * Should only be used when no other report methods fit the desired functionality
     * @param msg message to send to operators
     */
    virtual void reportMessage(std::string msg) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~ICommBoundary() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
