//
// Created by Jack Hester on 9/28/22.
//
#include <string>
#include "Strings.h"

const std::string errors::LOGGING_ERROR = "[-] ERROR: Logging of value(s) failed";
const std::string errors::FILE_NOT_FOUND_ERROR = "[-] ERROR: File not found";

sensorData::sensorAndValveDataNames getCSVColNames(){
    struct sensorData::sensorAndValveDataNames columnNames;

    columnNames.timestamp = "Epoch_Time";
    columnNames.loxVent = "LOX_Vent";
    columnNames.kerVent = "Ker_Vent";
    columnNames.loxDrip = "LOX_Drip";
    columnNames.kerDrip = "Ker_Drip";
    columnNames.loxPressurant = "LOX_Pressurant";
    columnNames.kerPressurant = "Ker_Pressurant";
    columnNames.loxFlow = "LOX_Flow";
    columnNames.kerFlow = "Ker_Flow";
    columnNames.loxPurge = "LOX_Purge";
    columnNames.kerPurge = "Ker_Purge";
    columnNames.loxTankDucer = "LOX_Tank_Ducer";
    columnNames.kerTankDucer = "Ker_Tank_Ducer";
    columnNames.purgeDucer = "Purge_Ducer";
    columnNames.loxInletDucer = "LOX_Inlet_Dcuer";
    columnNames.kerInletDucer = "Ker_Inlet_Ducer";
    columnNames.kerPintleDucer = "Ker_Pintle_Ducer";
    columnNames.loxVenturi = "LOX_Venturi";
    columnNames.kerVenturi = "Ker_Venturi";
    columnNames.pneumaticsDucer = "Pneumatics_Ducer";
    columnNames.loadCell = "Load_Cell";
    columnNames.loxTank1 = "LOX_Tank_1";
    columnNames.loxTank2 = "LOX_Tank_2";
    columnNames.loxTank3 = "LOX_Tank_3";
    columnNames.loxDripLine = "LOX_Drip_Line";
    columnNames.outsideThroat = "Outside_Throat";
    columnNames.nozzle = "Nozzle";

    return columnNames;
}



