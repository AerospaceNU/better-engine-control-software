//
// Created by Jack Hester on 6/13/22.
//

/**
 * Class for logging, brought over from the old ECS
 */
//TODO: get this class incorporated with the rest of the program

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H

#include <fstream>
//#include "utils.h"
#include "utils-and-constants/structs.h"
#include <string.h> //TODO: AHHHH I don't like this maybe we can do away with it later
#include "utils-and-constants/structs.h"


class Logger{
private:
    //std::ofstream m_csv_file;
    std::string m_csv_name;// = "logger_pi"+get_date()+".csv";
    unsigned long int m_posixTime;
    std::string m_ecsState;
    struct sensors m_sensorValues;
    struct valves m_valveValues;

public:
    std::ofstream m_csv_file;

    Logger(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues);

    void set_vals(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues);

    virtual void init_csv(); //TODO: set this back to virtual

    virtual bool write_row(); //TODO: set this back to virtual

    void close_csv();

};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
