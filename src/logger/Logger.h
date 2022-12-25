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
    /**
     * Constructs logger with no file to write to
     * (this object will do nothing if written to)
     */
    Logger();

    /**
     * Constructs logger to given file name
     * @param fileName
     */
    explicit Logger(const std::string& fileName);

    Logger(const Logger& other) = delete;
    Logger(Logger&& other) = default;

    Logger& operator=(const Logger& other) = delete;
    Logger& operator=(Logger&& other) = default;

    ~Logger() = default;

    /**
     * Writes string to file, ending with a new line
     *
     * If file object is not set, this will do nothing
     * @param str string to save
     */
    void write(const std::string& str);

private:
    std::ofstream fileObject;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
