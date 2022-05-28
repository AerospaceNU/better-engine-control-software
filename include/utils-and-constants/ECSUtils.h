#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H

#include <cstdint>
#include <chrono>

enum ECSValveState {
    OPEN,
    CLOSED,
    INVALID
};

enum ECSRedLineResponse{
    ABORT,
    WARN
};

enum ECSMessageType{
    ERROR,
    SENSORDATA,
    LOG
};

enum MessageResponse{
    SUCCESS,
    FAILURE
};

uint64_t getTimeStamp();

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
