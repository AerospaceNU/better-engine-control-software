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
enum class ECSValveState: uint8_t {
    OPEN = 1,
    CLOSED = 2,
    INVALID = 3
};



/**
 * An enum representing the available messages a IRedline will pass back
 */
enum class ECSRedLineResponse {
    ABORT,
    WARN,
    SAFE
};


//std::string get_date();


//TODO: figure out if get_posix() and getTimeStamp() are the same thing
unsigned long int get_posix();
/**
 * Helper function to return the current time as a unsigned 64 bit integer
 * @return current time in milliseconds
 */
uint64_t getTimeStamp();

/**
 * Filters out doubles with NaN value
 * @param check double to check if it's NaN or not
 * @return 0 if check was NaN, og value otherwise
 */
double filterDoubleNan(double check);

typedef unsigned long int posixLong;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_WATCHDOGREDLINES_H
