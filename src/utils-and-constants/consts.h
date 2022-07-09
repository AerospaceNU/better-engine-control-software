//
// Created by Jack Hester on 6/13/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H

#include <string> //TODO: hmmm maybe we can avoid this later
#include "structs.h"

namespace CommBoundary{
    //constants for sockets
    //extern const
    extern const std::string BROADCAST_PORT;
    //extern const
}

namespace consts{

    //native logger CSV column names initialized here
    extern const std::string csvColNames[19];

    //TODO: use these calibrations in the stand boundary
    //sensor calibrations initialized here
    extern const double loxInletDucer_calibration[3];
    extern const double kerInletDucer_calibration[3];
    extern const double purgeDucer_calibration[3];
    extern const double kerPintleDucer_calibration[3];
    extern const double loxTankDucer_calibration[3];
    extern const double kerTankDucer_calibration[3];
    extern const double pneumaticDucer_calibration[3];
    extern const double loxRegDucer_calibration[3];
    extern const double kerRegDucer_calibration[3];
    extern const double loxVenturi_calibration[3];
    extern const double kerVenturi_calibration[3];
    extern const double manifoldInletThermo_calibration[3];
    extern const double manifoldOutletThermo_calibration[3];
    extern const double tank1Thermo_calibration[3];
    extern const double tank2Thermo_calibration[3];
    extern const double tank3Thermo_calibration[3];
    extern const double loadCell_calibration[3];
}

//all error messages initialized here
namespace errors{
    extern const std::string LOGGING_ERROR;
    extern const std::string FILE_NOT_FOUND_ERROR;
    extern const std::string SOCKET_ERROR;
    extern const std::string INVALID_PARAM_ERROR;
    extern const std::string SOCKET_BINDING_ERROR;
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_CONSTS_H
