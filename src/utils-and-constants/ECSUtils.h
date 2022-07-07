#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H

#include <cstdint>
#include <chrono>

/**
 * An enum representing the possible readings of a valve
 *
 * NOTE: INVALID is not a valid valve command, only used from reading a valve
 */
enum class ECSValveState {
    OPEN,
    CLOSED,
    INVALID
};

/**
 * An enum representing the available messages a IRedline will pass back
 */
enum class ECSRedLineResponse{
    ABORT,
    WARN,
    SAFE
};

/**
 * TODO
 */
enum class ECSMessageType{
    SENSORDATA,
    LOG
};

/**
 * TODO
 */
enum class MessageResponse{
    SUCCESS,
    FAILURE
};

/**
 * Helper function to return the current time as a unsigned 64 bit integer
 * @return
 */
uint64_t getTimeStamp();

/**
 * TODO figure out what the fuck cam was doing here
 * @param check
 * @return
 */
// filters nan data values to 0
double filterNan(double check);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
