//
// Created by kevin on 8/2/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
#include <exception>

/**
 * Custom exception that is thrown when a effector errors (ex. fails to actuate a valve)
 */
class EffectorException: public std::exception {
public:
    //TODO: add more descriptive error message if required
    const char* what() const noexcept override{
        return "Effector error";
    }
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
