#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H

#include <cstdint>
#include <chrono>

enum class ECSValveState {
    OPEN,
    CLOSED,
    INVALID
};

enum class ECSRedLineResponse{
    ABORT,
    WARN
};

enum class ECSMessageType{
    SENSORDATA,
    LOG
};

enum class MessageResponse{
    SUCCESS,
    FAILURE
};

uint64_t getTimeStamp();

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
