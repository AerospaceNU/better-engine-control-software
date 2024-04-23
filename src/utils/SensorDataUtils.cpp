#include <cmath>
#include "SensorDataUtils.h"

#include <algorithm>
#include <concepts>

namespace{
    // apparently this shit can't be const
    int median(std::vector<int> &v) {
        size_t n = v.size() / 2;
        nth_element(v.begin(), v.begin() + n, v.end());
        return v[n];
    }

    // selectorField is a pointer-to-member, https://stackoverflow.com/a/4078006/12310828
    int getMedianOfSensorDataIntField(const std::vector<SensorData>& datas, int SensorData::* selectorField){
        std::vector<int> fields;        

        for (const auto& sensorData: datas){
            fields.emplace_back(sensorData.*selectorField);
        }

        return median(fields);
    }
}
/**
 * list out all of the different fields data from the sensordata & commanddata
 * check if all of the test are passing for all of the field cases
 */
SensorData medianData(std::vector<SensorData> datas) {
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    static_assert(SensorData::majorVersion == 7,
                  "Function not updated from SensorData change, please update this function and the static_assert");
    if (datas.empty()){
        return SensorData{};
    }
    
    SensorData result;

    result.loxVent = datas.back().loxVent;
    result.kerVent = datas.back().kerVent;
    result.loxDrip = datas.back().loxDrip;
    result.kerDrip = datas.back().kerDrip;
    result.loxPressurant = datas.back().loxPressurant;
    result.kerPressurant = datas.back().kerPressurant;
    result.loxFlow = datas.back().loxFlow;
    result.kerFlow = datas.back().kerFlow;
    result.loxPurge = datas.back().loxPurge;
    result.kerPurge = datas.back().kerPurge;
    result.kerOrifice = datas.back().kerOrifice;

    result.kerInletTC_Fault = datas.back().kerInletTC_Fault;
    result.kerOutletTC_Fault = datas.back().kerOutletTC_Fault;
    result.loxTankTC_Fault = datas.back().loxTankTC_Fault;
    result.miscTC_Fault = datas.back().miscTC_Fault;

    result.orificeDownstreamDucer = getMedianOfSensorDataIntField(datas, &SensorData::orificeDownstreamDucer);
    // result.kerTankDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerTankDucer;});
    // result.purgeDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.purgeDucer;});
    // result.loxInletDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxInletDucer;});
    result.kerInletDucer = getMedianOfSensorDataIntField(datas, &SensorData::kerInletDucer);
    result.kerPintleDucer = getMedianOfSensorDataIntField(datas, &SensorData::kerPintleDucer);
    result.loxVenturi = getMedianOfSensorDataIntField(datas, &SensorData::loxVenturi);
    result.loxVenturi2 = getMedianOfSensorDataIntField(datas, &SensorData::loxVenturi2);
    result.kerVenturi = getMedianOfSensorDataIntField(datas, &SensorData::kerVenturi);
    result.kerVenturi2 = getMedianOfSensorDataIntField(datas, &SensorData::kerVenturi2);

    result.pneumaticDucer = getMedianOfSensorDataIntField(datas, &SensorData::pneumaticDucer);

    result.loadCell = getMedianOfSensorDataIntField(datas, &SensorData::loadCell);

    result.loxRegDucer = getMedianOfSensorDataIntField(datas, &SensorData::loxRegDucer);
    result.kerRegDucer = getMedianOfSensorDataIntField(datas, &SensorData::kerRegDucer);
    //  result.n2pressDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.n2pressDucer;});
    result.orificeUpstreamDucer = getMedianOfSensorDataIntField(datas, &SensorData::orificeUpstreamDucer);

    result.loxTankTC = getMedianOfSensorDataIntField(datas, &SensorData::loxTankTC);
    result.kerInletTC = getMedianOfSensorDataIntField(datas, &SensorData::kerInletTC);
    result.kerOutletTC = getMedianOfSensorDataIntField(datas, &SensorData::kerOutletTC);
    result.miscTC = getMedianOfSensorDataIntField(datas, &SensorData::miscTC);
    result.boardTemp = getMedianOfSensorDataIntField(datas, &SensorData::boardTemp);

    return result;
}

namespace{
    // selectorField is a pointer-to-member, https://stackoverflow.com/a/4078006/12310828
    int getAverageOfSensorDataIntField(const std::vector<SensorData>& datas, int SensorData::* selectorField){
        //TODO: we gotta be careful for int overflow here

        double i = 1;
        double currentAvg = 0;
        for (const auto& sensorData: datas){
            // Aaron's Algorithm for Average
            // The average is a simplified version of A' =(A(n-1) + a)/n
            //    where A' is the new average at n, A is the current average at n - 1, and a is the value at n
            currentAvg *= 1 - (1.0 / i);
            currentAvg += (sensorData.*selectorField) / i;
            i++;
        }

        // TODO: this cast is technically iffy, but once we switch to fixed size vectors we should be safe
        return static_cast<int>(currentAvg);
    }
}

/**
 * list out all of the different fields data from the sensordata & commanddata
 * check if all of the test are passing for all of the field cases
 */
SensorData averageData(std::vector<SensorData> datas) {
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    static_assert(SensorData::majorVersion == 7,
                  "Function not updated from SensorData change, please update this function and the static_assert");
    if (datas.empty()){
        return SensorData{};
    }

    SensorData result;

    result.loxVent = datas.back().loxVent;
    result.kerVent = datas.back().kerVent;
    result.loxDrip = datas.back().loxDrip;
    result.kerDrip = datas.back().kerDrip;
    result.loxPressurant = datas.back().loxPressurant;
    result.kerPressurant = datas.back().kerPressurant;
    result.loxFlow = datas.back().loxFlow;
    result.kerFlow = datas.back().kerFlow;
    result.loxPurge = datas.back().loxPurge;
    result.kerPurge = datas.back().kerPurge;
    result.kerOrifice = datas.back().kerOrifice;

    result.kerInletTC_Fault = datas.back().kerInletTC_Fault;
    result.kerOutletTC_Fault = datas.back().kerOutletTC_Fault;
    result.loxTankTC_Fault = datas.back().loxTankTC_Fault;
    result.miscTC_Fault = datas.back().miscTC_Fault;

    result.orificeDownstreamDucer = getAverageOfSensorDataIntField(datas, &SensorData::orificeDownstreamDucer);
    // result.kerTankDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerTankDucer;});
    // result.purgeDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.purgeDucer;});
    // result.loxInletDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxInletDucer;});
    result.kerInletDucer = getAverageOfSensorDataIntField(datas, &SensorData::kerInletDucer);
    result.kerPintleDucer = getAverageOfSensorDataIntField(datas, &SensorData::kerPintleDucer);
    result.loxVenturi = getAverageOfSensorDataIntField(datas, &SensorData::loxVenturi);
    result.loxVenturi2 = getAverageOfSensorDataIntField(datas, &SensorData::loxVenturi2);
    result.kerVenturi = getAverageOfSensorDataIntField(datas, &SensorData::kerVenturi);
    result.kerVenturi2 = getAverageOfSensorDataIntField(datas, &SensorData::kerVenturi2);

    result.pneumaticDucer = getAverageOfSensorDataIntField(datas, &SensorData::pneumaticDucer);

    result.loadCell = getAverageOfSensorDataIntField(datas, &SensorData::loadCell);

    result.loxRegDucer = getAverageOfSensorDataIntField(datas, &SensorData::loxRegDucer);
    result.kerRegDucer = getAverageOfSensorDataIntField(datas, &SensorData::kerRegDucer);
    // result.n2pressDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.n2pressDucer;});

    result.orificeUpstreamDucer = getAverageOfSensorDataIntField(datas, &SensorData::orificeUpstreamDucer);

    result.loxTankTC = getAverageOfSensorDataIntField(datas, &SensorData::loxTankTC);
    result.kerInletTC = getAverageOfSensorDataIntField(datas, &SensorData::kerInletTC);
    result.kerOutletTC = getAverageOfSensorDataIntField(datas, &SensorData::kerOutletTC);
    result.miscTC = getAverageOfSensorDataIntField(datas, &SensorData::miscTC);
    result.boardTemp = getAverageOfSensorDataIntField(datas, &SensorData::boardTemp);

    return result;

}
