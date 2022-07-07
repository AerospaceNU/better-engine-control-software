//
// Created by Jack Hester on 6/11/2022.
//
#include "Logger.h"
#include <iostream>
#include "util/consts.h"

using namespace std;

/*
 * Initialize the logger and set values
 */
Logger::Logger(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues){
    set_vals(csv_name, posixTime, std::move(ecsState), sensorValues, valveValues);
};

/*
 * set_vals
 * @param csv_name a string of what to call/where to save the csv log file
 * @param posixTime a long int with the current posix/unix time
 * @param ecs_state a string of the current ECS state
 * @param sensorValues a struct containing all sensor readings from the stand (defined in structs.h)
 * @param sensorValues a struct containing all valve states from the stand (defined in structs.h)
 */
void Logger::set_vals(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues){
    m_csv_name = csv_name;
    m_posixTime = posixTime;
    m_ecsState = ecsState;
    m_sensorValues = sensorValues;
    m_valveValues = valveValues;
};

/*
 * init_csv
 * starts up a csv, then fills in the top row based on the csvColNames defined in consts.h
 */
void Logger::init_csv(){
    m_csv_file.open(m_csv_name);
    int array_size = *(&consts::csvColNames + 1) - consts::csvColNames;
    for (int i = 0; i < array_size; i++) {
        m_csv_file << consts::csvColNames[i] << ",";
    }
    m_csv_file << "\n";
}

/*
    * write_row
    * returns a boolean of true if writing a row was successful, false if something went wrong
    * try/catch serves as protection to keep from crashing, bool alerts us if logging is failings
*/
bool Logger::write_row() {
    try{
        m_csv_file << m_posixTime << ",";
        m_csv_file << m_ecsState << ",";
        m_csv_file << m_sensorValues.loxInletDucer << ",";
        m_csv_file << m_sensorValues.kerInletDucer << ",";
        m_csv_file << m_sensorValues.purgeDucer << ",";
        m_csv_file << m_sensorValues.kerPintleDucer << ",";
        m_csv_file << m_sensorValues.loxTankDucer << ",";
        m_csv_file << m_sensorValues.kerTankDucer << ",";
        m_csv_file << m_sensorValues.pneumaticDucer << ",";
        m_csv_file << m_sensorValues.loxN2Ducer << ",";
        m_csv_file << m_sensorValues.kerN2Ducer << ",";
        m_csv_file << m_sensorValues.loxVenturi << ",";
        m_csv_file << m_sensorValues.kerVenturi << ",";
        m_csv_file << m_sensorValues.manifoldInletThermo << ",";
        m_csv_file << m_sensorValues.manifoldOutletThermo << ",";
        m_csv_file << m_sensorValues.tank1Thermo << ",";
        m_csv_file << m_sensorValues.tank2Thermo << ",";
        m_csv_file << m_sensorValues.tank3Thermo << ",";
        m_csv_file << m_sensorValues.loadCell << ",";
        //TODO: add the valve states
        m_csv_file << "\n";
        return true;
        //throw();
    } catch(...){
        std::cout << errors::LOGGING_ERORR << std::endl;
        return false;
    }
}

/*
    * close_csv
    * close the csv file and end writing
    * not virtual because killing the ECS main loop with control+c will end this anyway, but a graceful close is ideal
*/
void Logger::close_csv(){
    m_csv_file.close();
    //TODO: implement a check if the csv is not actually open so we don't get wild errors
};
