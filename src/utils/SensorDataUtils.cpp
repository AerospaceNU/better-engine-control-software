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

    int getMedianOfSensorDataIntField(const std::vector<SensorData>& datas, int (*selectorFct)(const SensorData&)){
        std::vector<int> fields;        

        for (const auto& sensorData: datas){
            fields.emplace_back(selectorFct(sensorData));
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
    static_assert(SensorData::majorVersion == 8,
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

    result.orificeDownstreamDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.orificeDownstreamDucer;});
    // result.kerTankDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerTankDucer;});
    // result.purgeDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.purgeDucer;});
    // result.loxInletDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxInletDucer;});
    result.kerInletDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerInletDucer;});
    result.kerPintleDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerPintleDucer;});
    result.loxVenturi = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxVenturi;});
    result.loxVenturi2 = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxVenturi2;});
    result.kerVenturi = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerVenturi;});
    result.kerVenturi2 = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerVenturi2;});

    result.pneumaticDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.pneumaticDucer;});

    result.loadCell = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loadCell;});

    result.loxRegDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxRegDucer;});
    result.kerRegDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerRegDucer;});
    result.n2pressDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.n2pressDucer;}); //added
    result.loxTankDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxTankDucer;}); //added
    result.loxFlowDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxFlowDucer;}); //added
    result.orificeUpstreamDucer = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.orificeUpstreamDucer;});

    result.loxTankTC = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.loxTankTC;});
    result.kerInletTC = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerInletTC;});
    result.kerOutletTC = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.kerOutletTC;});
    result.miscTC = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.miscTC;});
    result.boardTemp = getMedianOfSensorDataIntField(datas, [](const SensorData& data){return data.boardTemp;});

    return result;

}

namespace{
    int getAverageOfSensorDataIntField(const std::vector<SensorData>& datas, int (*selectorFct)(const SensorData&)){
        //TODO: we gotta be careful for int overflow here

        double i = 1;
        double currentAvg = 0;
        for (const auto& sensorData: datas){
            // Aaron's Algorithm for Average
            // The average is a simplified version of A' =(A(n-1) + a)/n
            //    where A' is the new average at n, A is the current average at n - 1, and a is the value at n
            currentAvg *= 1 - (1.0 / i);
            currentAvg += selectorFct(sensorData) / i;
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
    static_assert(SensorData::majorVersion == 8,
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

    result.orificeDownstreamDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.orificeDownstreamDucer;});
    // result.kerTankDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerTankDucer;});
    // result.purgeDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.purgeDucer;});
    // result.loxInletDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxInletDucer;});
    result.kerInletDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerInletDucer;});
    result.kerPintleDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerPintleDucer;});
    result.loxVenturi = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxVenturi;});
    result.loxVenturi2 = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxVenturi2;});
    result.kerVenturi = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerVenturi;});
    result.kerVenturi2 = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerVenturi2;});

    result.pneumaticDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.pneumaticDucer;});

    result.loadCell = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loadCell;});

    result.loxRegDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxRegDucer;});
    result.kerRegDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerRegDucer;});

    result.n2pressDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.n2pressDucer;}); //added
    result.loxTankDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxTankDucer;}); //added
     result.loxFlowDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxFlowDucer;}); //added

    result.orificeUpstreamDucer = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.orificeUpstreamDucer;});

    result.loxTankTC = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.loxTankTC;});
    result.kerInletTC = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerInletTC;});
    result.kerOutletTC = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.kerOutletTC;});
    result.miscTC = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.miscTC;});
    result.boardTemp = getAverageOfSensorDataIntField(datas, [](const SensorData& data){return data.boardTemp;});

    return result;

}
