//
// Created by Jack Hester on 6/13/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H

#include <fstream>
#include <string>

/**
 * Class for logging
 */
class Logger{
public:
    Logger();
    explicit Logger(const std::string& csv_name);

    Logger(const Logger& other) = delete;
    Logger(Logger&& other) = default;

    Logger& operator=(const Logger& other) = delete;
    Logger& operator=(Logger&& other) = default;

    ~Logger() = default;

    void write(const std::string& str);

private:
    std::ofstream fileObject;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
