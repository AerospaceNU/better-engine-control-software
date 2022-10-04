//
// Created by Jack Hester on 6/13/22.
//

/**
 * Class for logging
 */
#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H

#include <fstream>
//#include "utils.h"
//#include "utils-and-constants/structs.h"
#include "../utils/SensorData.h"
#include "Strings.h"


class Logger{
private:
    //std::ofstream m_csv_file;
    std::string m_csv_name;// = "logger_pi"+get_date()+".csv";
    //unsigned long int m_posixTime;
    //std::string m_ecsState;
    //struct sensors m_sensorValues;
    //struct valves m_valveValues;

public:
    std::ofstream m_csv_file;

    explicit Logger(std::string csv_name);

    //void set_vals(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues);

    void set_csv_name(std::string csv_name);

    void init_csv();

    bool write_row(SensorData currData);

    //virtual bool write_row(SensorData currData);

    void close_csv();
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LOGGER_H
