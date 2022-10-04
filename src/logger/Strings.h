//
// Created by Jack Hester on 9/28/22.
//

#include <string>

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_STRINGS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_STRINGS_H

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_STRINGS_H

namespace errors{
    extern const std::string LOGGING_ERROR;
    extern const std::string FILE_NOT_FOUND_ERROR;
}

namespace sensorData{
    struct sensorAndValveDataNames{
        std::string timestamp;

        std::string loxVent;
        std::string kerVent;
        std::string loxDrip;
        std::string kerDrip;
        std::string loxPressurant;
        std::string kerPressurant;
        std::string loxFlow;
        std::string kerFlow;
        std::string loxPurge;
        std::string kerPurge;

        std::string loxTankDucer;
        std::string kerTankDucer;
        std::string purgeDucer;
        std::string loxInletDucer;
        std::string kerInletDucer;
        std::string kerPintleDucer;
        std::string loxVenturi;
        std::string kerVenturi;

        std::string pneumaticsDucer;
        std::string loadCell;

        std::string loxTank1;
        std::string loxTank2;
        std::string loxTank3;
        std::string loxDripLine;
        std::string outsideThroat;
        std::string nozzle;
    };

}

sensorData::sensorAndValveDataNames getCSVColNames();

