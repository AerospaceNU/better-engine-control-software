//
// Created by Jack Hester on 6/11/2022.
//
#include "Logger.h"
#include <iostream>
//#include "../utils/SensorData.h"
//#include "../constants/Strings.h"

using namespace std;

/*
 * Initialize the logger and set values
 */
Logger::Logger(std::string csv_name){
    set_csv_name(csv_name);
    //set_vals(csv_name, posixTime, std::move(ecsState), sensorValues, valveValues);
};

void Logger::set_csv_name(std::string csv_name){
    m_csv_name = csv_name;
}

/*
 * set_vals
 * @param csv_name a string of what to call/where to save the csv log file
 * @param posixTime a long int with the current posix/unix time
 * @param ecs_state a string of the current ECS state
 * @param sensorValues a struct containing all sensor readings from the stand (defined in structs.h)
 * @param sensorValues a struct containing all valve states from the stand (defined in structs.h)
 */
//void Logger::set_vals(std::string csv_name, long int posixTime, std::string ecsState, sensors sensorValues, valves valveValues){
//    m_csv_name = csv_name;
//    m_posixTime = posixTime;
//    m_ecsState = ecsState;
//    m_sensorValues = sensorValues;
//    m_valveValues = valveValues;
//};

/*
 * init_csv
 * starts up a csv, then fills in the top row based on the csvColNames defined in consts.h
 */
void Logger::init_csv(){
    m_csv_file.open(m_csv_name);
    struct sensorData::sensorAndValveDataNames loggerColNames = getCSVColNames();

    m_csv_file << loggerColNames.timestamp << ",";
    m_csv_file << loggerColNames.loxVent << ",";
    m_csv_file << loggerColNames.kerVent << ",";
    m_csv_file << loggerColNames.loxDrip << ",";
    m_csv_file << loggerColNames.kerDrip << ",";
    m_csv_file << loggerColNames.loxPressurant << ",";
    m_csv_file << loggerColNames.kerPressurant << ",";
    m_csv_file << loggerColNames.loxFlow << ",";
    m_csv_file << loggerColNames.kerFlow << ",";
    m_csv_file << loggerColNames.loxPurge << ",";
    m_csv_file << loggerColNames.kerPurge << ",";

    m_csv_file << loggerColNames.loxTankDucer << ",";
    m_csv_file << loggerColNames.kerTankDucer << ",";
    m_csv_file << loggerColNames.purgeDucer << ",";
    m_csv_file << loggerColNames.loxInletDucer << ",";
    m_csv_file << loggerColNames.kerInletDucer << ",";
    m_csv_file << loggerColNames.kerPintleDucer << ",";
    m_csv_file << loggerColNames.loxVenturi << ",";
    m_csv_file << loggerColNames.kerVenturi << ",";

    m_csv_file << loggerColNames.pneumaticsDucer << ",";
    m_csv_file << loggerColNames.loadCell << ",";

    m_csv_file << loggerColNames.loxTank1 << ",";
    m_csv_file << loggerColNames.loxTank2 << ",";
    m_csv_file << loggerColNames.loxTank3 << ",";
    m_csv_file << loggerColNames.loxDripLine << ",";
    m_csv_file << loggerColNames.outsideThroat << ",";
    m_csv_file << loggerColNames.nozzle << ",";

    m_csv_file << "\n";
}

/*
    * write_row
    * takes in a sensor data struct
    * returns a boolean of true if writing a row was successful, false if something went wrong
    * try/catch serves as protection to keep from crashing, bool alerts us if logging is failings
*/
bool Logger::write_row(SensorData currData) {
    try{
        m_csv_file << getTimeStamp() << ",";
        //TODO: does casting to double cause us problems?
        m_csv_file << static_cast<int>(currData.loxVent) << ",";
        m_csv_file << static_cast<int>(currData.kerVent) << ",";
        m_csv_file << static_cast<int>(currData.loxDrip) << ",";
        m_csv_file << static_cast<int>(currData.kerDrip) << ",";
        m_csv_file << static_cast<int>(currData.loxPressurant) << ",";
        m_csv_file << static_cast<int>(currData.kerPressurant) << ",";
        m_csv_file << static_cast<int>(currData.loxFlow) << ",";
        m_csv_file << static_cast<int>(currData.kerFlow) << ",";
        m_csv_file << static_cast<int>(currData.loxPurge) << ",";
        m_csv_file <<  static_cast<int>(currData.kerPurge) << ",";


        m_csv_file << currData.loxTankDucer << ",";
        m_csv_file << currData.kerTankDucer << ",";
        m_csv_file << currData.purgeDucer << ",";
        m_csv_file << currData.loxInletDucer << ",";
        m_csv_file << currData.kerInletDucer << ",";
        m_csv_file << currData.kerPintleDucer << ",";
        m_csv_file << currData.loxVenturi << ",";
        m_csv_file << currData.kerVenturi << ",";

        m_csv_file << currData.pnematicsDucer << ",";
        m_csv_file << currData.loadCell << ",";

        m_csv_file << currData.loxTank1 << ",";
        m_csv_file << currData.loxTank2 << ",";
        m_csv_file << currData.loxTank3 << ",";
        m_csv_file << currData.loxDripLine << ",";
        m_csv_file << currData.outsideThroat << ",";
        m_csv_file << currData.nozzle << ",";

        m_csv_file << "\n";

        return true;
        //throw();
    } catch(...){
        std::cout << errors::LOGGING_ERROR << std::endl;
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
