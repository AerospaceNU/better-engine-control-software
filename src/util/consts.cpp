//
// Created by Jack Hester on 6/21/22.
//
#include "consts.h"
#include "structs.h"

using namespace consts;

//column names for native logger CSV file declared here //TODO: add valve states
const std::string consts::csvColNames[19] = {"time","state","loxInletDucer","kerInletDucer","purgeDucer",
"kerPintleDucer", "loxTankDucer", "kerTankDucer", "pneumaticDucer",
"loxN2Ducer","kerN2Ducer","loxVenturi", "kerVenturi",
"manifoldInletThermo","manifoldOutletThermo","tank1Thermo","tank2Thermo",
"tank3Thermo", "loadCell"};

//sensor calibration values declared here
const double consts::loxInletDucer_calibration[3] = {0.714, 0.0375, 0};
const double consts::kerInletDucer_calibration[3] = {5.34, 0.0375, 0};
const double consts::purgeDucer_calibration[3] =  {-0.577, 0.0375, 0};
const double consts::kerPintleDucer_calibration[3] = {-0.954, 0.0375, 0};
const double consts::loxTankDucer_calibration[3] = {0.9087, 0.0377, 0};
const double consts::kerTankDucer_calibration[3] = {0.365, 0.0376, 0};
const double consts::pneumaticDucer_calibration[3] =  {-0.0888, 0.0101, 0};
const double consts::loxRegDucer_calibration[3] = {0, 1, 0};
const double consts::kerRegDucer_calibration[3] =  {0, 1, 0};
const double consts::loxVenturi_calibration[3] = {-1.97, 0.019, 0};
const double consts::kerVenturi_calibration[3] = {0.34, 0.019, 0};
const double consts::manifoldInletThermo_calibration[3] =  {0, 1, 0};
const double consts::manifoldOutletThermo_calibration[3] = {0, 1, 0};
const double consts::tank1Thermo_calibration[3] = {0, 1, 0};
const double consts::tank2Thermo_calibration[3] = {0, 1, 0};
const double consts::tank3Thermo_calibration[3] = {0, 1, 0};
const double consts::loadCell_calibration[3] = {0, 1, 0};

using namespace errors;

//error messages declared here
const std::string errors::LOGGING_ERORR = "[-] ERROR: Logging of value(s) failed";
const std::string errors::FILE_NOT_FOUND_ERROR = "[-] ERROR: File not found";
const std::string errors::SOCKET_ERROR = "[-] ERROR: Socket error";
const std::string errors::INVALID_PARAM_ERROR = "[-] ERROR: Invalid parameter provided to function";