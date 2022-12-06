#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H

#include <cstdint>
#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>

/**
 * Method that allows construction of vector of unique_ptrs similar to the standard initializer list
 * which doesnt work for unique _ptrs
 * bc C++ is dumb.
 * @tparam V type of the unique_ptr
 * @tparam Args gonna be real chief i dunno wtf this is
 * i copied this from https://stackoverflow.com/a/73674943/12310828
 * @param args elements of the vector
 * @return vector of type std::unique_ptr<V>
 */
template <class V, class ... Args> auto make_vector_unique(Args ... args) {
    std::vector<std::unique_ptr<V>> rv;
    (rv.emplace_back(std::move(args)), ...);
    return rv;
}


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

/**
 * Really fucked up method to get current date and time date formatted in a string
 *  (fuck you C++ why are all your methods for dates dogshit)
 * @return a string with the current date in the format of YYYY-(M)M-(D)D_(H)H-(M)M-(S)S e.g., 2022-6-13_15-4-6
 */
std::string get_date();

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H
