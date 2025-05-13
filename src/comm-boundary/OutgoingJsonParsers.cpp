//
// Created by kevin on 12/20/2022.
//

#include "OutgoingJsonParsers.h"
#include "ParsingHelpers.h"
#include "utils/ECSUtils.h"

// anonymous namespace for helper functions
namespace{
    /**
     * Helper function, parses valves in sensor data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
     * This function should hit all the valve fields in SensorData
     */
    json getValveReport(const SensorData& data) {
        static_assert(CommandData::majorVersion == 4,
                      "Function not updated from CommandData change, please update this function and the static_assert");
        json valveReport;

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxVent);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxVent"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerVent);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerVent"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxDrip);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxDrip"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerDrip);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerDrip"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxPressurant);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxPressurant"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerPressurant);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerPressurant"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxFlow);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxFlow"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerFlow);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerFlow"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.loxPurge);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["loxPurge"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerPurge);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerPurge"] = curReport;
        }

        {
            json curReport;
            curReport["valveState"] = valveStateToString(data.kerOrifice);
            curReport["timeStamp"] = getTimeStamp();

            valveReport["kerOrifice"] = curReport;
        }
        return valveReport;
    }

    /**
     * Helper function, parses pressure sensors in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
     * This function should hit all the fields containing data from pressure sensors
     * (this is not directly documented in SensorData, ask for documentation from
     * prop software lead or prop directly)
     */
    json getPressureReport(const SensorData& data) {
        static_assert(SensorData::majorVersion == 9,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        json pressureReport;

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.orificeDownstreamDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["orificeDownstreamDucer"] = curReport;
        // }

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.kerTankDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["kerTankDucer"] = curReport;
        // }

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.purgeDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["purgeDucer"] = curReport;
        // }

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.loxInletDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["loxInletDucer"] = curReport;
        // }

        {
            json curReport;
            curReport["sensorReading"] = data.kerInletDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerInletDucer"] = curReport;
        }

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.kerPintleDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["kerPintleDucer"] = curReport;
        // }

        {
            json curReport;
            curReport["sensorReading"] = data.loxVenturi;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxVenturi"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxVenturi2;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxVenturi2"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerVenturi;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerVenturi"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerVenturi2;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerVenturi2"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.chamberDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["chamberDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.pneumaticDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["pneumaticDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxRegDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["loxRegDucer"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerRegDucer;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            pressureReport["kerRegDucer"] = curReport;
        }

        { //added
             json curReport;
             curReport["sensorReading"] = data.n2pressDucer;
             curReport["unit"] = "psi";
             curReport["timeStamp"] = getTimeStamp();

             pressureReport["n2pressDucer"] = curReport;
        }
        { //added
             json curReport;
             curReport["sensorReading"] = data.loxFlowDucer;
             curReport["unit"] = "psi";
             curReport["timeStamp"] = getTimeStamp();

             pressureReport["loxFlowDucer"] = curReport;
        }
        { //added
             json curReport;
             curReport["sensorReading"] = data.loxTankDucer;
             curReport["unit"] = "psi";
             curReport["timeStamp"] = getTimeStamp();

             pressureReport["loxTankDucer"] = curReport;
        }

        // {
        //     json curReport;
        //     curReport["sensorReading"] = data.orificeUpstreamDucer;
        //     curReport["unit"] = "psi";
        //     curReport["timeStamp"] = getTimeStamp();

        //     pressureReport["orificeUpstreamDucer"] = curReport;
        // }

        { //added 3-16
            json kerFlowDucer;
            kerFlowDucer["sensorReading"] = data.kerFlowDucer;
            kerFlowDucer["unit"] = "psi";
            kerFlowDucer["timeStamp"] = getTimeStamp();

            pressureReport["kerFlowDucer"] = kerFlowDucer;
        }

        return pressureReport;
    }

    /**
     * Helper function, parses load cell sensors in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
    * This function should hit all the fields containing data from loadcell sensors
    * (this might not be directly documented in SensorData, if so ask for documentation from
    * prop software lead or prop directly)
    */
    json getLoadCellReport(const SensorData& data) {
        static_assert(SensorData::majorVersion == 9,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        json loadCellReport;

        {
            json curReport;
            curReport["sensorReading"] = data.loadCell;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();

            loadCellReport["loadCell"] = curReport;
        }

        return loadCellReport;
    }

    /**
     * Helper function, parses thermocouples in data into json for sending back
     * @param data sensor data to read
     * @return json object
     */
    /*
    * This function should hit all the fields containing data from thermocouples (sensors that measure temp)
    * (this is not directly documented in SensorData, ask for documentation from
    * prop software lead or prop directly)
    */
    json getTemperatureReport(const SensorData& data) {
        static_assert(SensorData::majorVersion == 9,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        json tempReport;

        {
            json curReport;
            curReport["sensorReading"] = data.boardTemp;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();
            curReport["fault"] = 0; // no fault flag

            tempReport["boardTemp"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.loxTankTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();
            curReport["fault"] = data.kerInletTC_Fault;

            tempReport["loxTankTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerInletTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();
            curReport["fault"] = data.kerOutletTC_Fault;

            tempReport["kerInletTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.kerOutletTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();
            curReport["fault"] = data.loxTankTC_Fault;

            tempReport["kerOutletTC"] = curReport;
        }

        {
            json curReport;
            curReport["sensorReading"] = data.miscTC;
            curReport["unit"] = "psi";
            curReport["timeStamp"] = getTimeStamp();
            curReport["fault"] = data.miscTC_Fault;

            tempReport["miscTC"] = curReport;
        }

        return tempReport;
    }
}


json parseECSState(ECSState& curState){
    json state;
    state["command"] = "STATE_TRANSITION";
    state["newState"] = curState.getName();
    state["timeStamp"] = getTimeStamp();
    return state;
}

json parseRedlines(const std::vector<RedlineResponsePacket>& redlineReports){
    json report;
    report["command"] = "REDLINE_REPORT";

    json inner_dict;
    for (auto& packet: redlineReports){

        json curReport;

        switch(packet.response){
            case ECSRedLineResponse::ABORT:
                curReport["report"] = "ABORT";
                break;
            case ECSRedLineResponse::WARN:
                curReport["report"] = "WARN";
                break;
            case ECSRedLineResponse::SAFE:
                curReport["report"] = "SAFE";
                break;
        }

        inner_dict[packet.redlineName] = curReport;
    }

    report["redlines"] = inner_dict;
    report["timeStamp"] = getTimeStamp();

    return report;
}

json parseSensorData(const SensorData& data, bool isCalibrated){
    json report;
    report["command"] = "DATA";
    report["timeStamp"] = getTimeStamp();

    if (isCalibrated) {
        report["calibrated?"] = "true";
    }
    else {
        report["calibrated?"] = "false";
    }

    json dataReport;
    dataReport["valves"] = ::getValveReport(data);
    dataReport["pressureSensors"] = ::getPressureReport(data);
    dataReport["loadCellSensors"] = ::getLoadCellReport(data);
    dataReport["tempSensors"] = ::getTemperatureReport(data);

    report["data"] = dataReport;
    report["timeStamp"] = getTimeStamp();

    return report;
}

json parseMessage(const std::string& message){
    json report;
    report["statement"] = message;
    report["command"] = "MESSAGE";
    report["timeStamp"] = getTimeStamp();
    return report;
}
