//
// Created by kevin on 8/2/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
#include <exception>
#include <string>

/**
 * Custom exception that is thrown when a effector errors (ex. fails to actuate a valve)
 */
class EffectorException: public std::exception {
public:
    explicit EffectorException(std::string errorMsg):
        errorMessage(std::move(errorMsg))
    {}

    [[nodiscard]] const char* what() const noexcept override{
        return this->errorMessage.c_str();
    }
private:
    std::string errorMessage;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_EFFECTOREXCEPTION_H
