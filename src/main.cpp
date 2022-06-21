//
// Created by Matthew Coughlin on 2/23/22.
//
#include <iostream>
/*#include "ECS.h"
#include "IBoundary.h"
#include "FakeBoundary.h"*/
#include "util/utils.h"
#include "Logger.h"
#include "util/structs.h"
#include "util/consts.h"

using namespace std;

int main() {
    /*IBoundary* boundary = new FakeBoundary();
    ECS* ecs = new ECS(boundary);
    ecs->run();*/

    //std::cout << get_posix() << std::endl;

    //get_posix();
    //std::cout << get_date() << std::endl;


    std::string csv_name_test = "logger_pi"+get_date()+".csv";
    std::string state_test = "ONLINE_SAFE_TEST";

    sensors sensor_test;
    sensor_test.loxInletDucer = 0.1;
    sensor_test.kerInletDucer = 0.1;
    sensor_test.purgeDucer = 0.1;
    sensor_test.kerPintleDucer = 0.1;
    sensor_test.loxTankDucer = 0.4;
    sensor_test.kerTankDucer = 0.1;
    sensor_test.pneumaticDucer = 0.1;
    sensor_test.loxN2Ducer = 0.3;
    sensor_test.kerN2Ducer = 0.3;
    sensor_test.loxVenturi = 0.3;
    sensor_test.kerVenturi = 0.3;
    sensor_test.manifoldInletThermo = 0.2;
    sensor_test.manifoldOutletThermo = 0.2;
    sensor_test.tank1Thermo = 0.2;
    sensor_test.tank2Thermo = 0.2;
    sensor_test.tank3Thermo = 0.2;
    sensor_test.loadCell = 0.5;

    valves valve_test;
    valve_test.kerDrip = false;
    valve_test.kerFlow = false;
    valve_test.kerPressurant = true;
    valve_test.kerPurge = false;
    valve_test.loxPressurant = false;
    valve_test.loxPurge = true;
    valve_test.kerPurge = false;
    valve_test.loxVent = false;
    valve_test.loxFlow = false;
    valve_test.kerVent = false;

    //TODO: note that lox and ker drip are not controlled pneumatically now, just manually

    //std::cout << get_posix() << std::endl;

    Logger* logger_demo = new Logger(csv_name_test, get_posix(), state_test, sensor_test, valve_test);

    /*logger_demo->init_csv();
    logger_demo->write_row();*/
    //logger_demo->close_csv();



    sensor_test.loadCell = 110.0;

    logger_demo->set_vals(csv_name_test, get_posix(), state_test, sensor_test, valve_test);

    /*logger_demo->write_row();
    logger_demo->close_csv();*/

    std::cout << "done!" << std::endl;

    //std::cout << consts::csvColNames[0] << std::endl;
    std::cout << consts::loxVenturi_calibration[1] << std::endl;

    std::cout << errors::FILE_NOT_FOUND_ERROR << std::endl;

    return 0;
}