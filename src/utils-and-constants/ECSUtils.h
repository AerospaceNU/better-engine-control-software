#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H

#include <cstdint>
#include <chrono>
#include <string>

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
enum class MessageResponse{
    SUCCESS,
    FAILURE
};


//TODO: figure out if we really need this? i think the enum setup we have is better than the bool
std::string bool_to_str(bool state);

std::string get_date();


//TODO: figure out if get_posix() and getTimeStamp() are the same thing
unsigned long int get_posix();
/**
 * Helper function to return the current time as a unsigned 64 bit integer
 * @return
 */
uint64_t getTimeStamp();


double filterDoubleNan(double check);

typedef unsigned long int posixLong;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
