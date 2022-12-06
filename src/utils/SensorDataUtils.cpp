#include <cmath>
#include "SensorDataUtils.h"

#include <algorithm>
#include <vector>

namespace {
    int median(std::vector<int> &v) {
        size_t n = v.size() / 2;
        nth_element(v.begin(), v.begin() + n, v.end());
        return v[n];
    }
}

/**
 * list out all of the different fields data from the sensordata & commanddata
 * check if all of the test are passing for all of the field cases
 */
SensorData medianData(std::vector<SensorData> data) {
    static_assert(SensorData::majorVersion == 3,
                  "Function not updated from SensorData change, please update this function and the static_assert");
    SensorData result;
    std::vector<int> loxTankDucervect;
    std::vector<int> kerTankDucervect;
    std::vector<int> purgeDucervect;
    std::vector<int> loxInletDucervect;
    std::vector<int> kerInletDucervect;
    std::vector<int> kerPintleDucervect;
    std::vector<int> loxVenturivect;
    std::vector<int> kerVenturivect;
    std::vector<int> pnematicsDucervect;
    std::vector<int> loadCellvect;
    std::vector<int> loxRegDucervect;
    std::vector<int> kerRegDucervect;
    std::vector<int> n2pressDucervect;
    std::vector<int> loxTankTCvect;
    std::vector<int> kerInletTCvect;
    std::vector<int> kerOutletTCvect;
    std::vector<int> miscTCvect;

    if (data.empty()) {
        return result;
    } else {

// back() called on empty vector??
        for (SensorData curData: data) {
            loxTankDucervect.push_back(curData.loxTankDucer);
            kerTankDucervect.push_back(curData.kerTankDucer);
            purgeDucervect.push_back(curData.purgeDucer);
            loxInletDucervect.push_back(curData.loxInletDucer);
            kerInletDucervect.push_back(curData.kerInletDucer);
            kerPintleDucervect.push_back(curData.kerPintleDucer);
            loxVenturivect.push_back(curData.loxVenturi);
            kerVenturivect.push_back(curData.kerVenturi);

            pnematicsDucervect.push_back(curData.pneumaticDucer);
            //changed^
            loadCellvect.push_back(curData.loadCell);

            loxRegDucervect.push_back(curData.loxRegDucer);
            kerRegDucervect.push_back(curData.kerRegDucer);
            n2pressDucervect.push_back(curData.n2pressDucer);
            loxTankTCvect.push_back(curData.loxTankTC);
            kerInletTCvect.push_back(curData.kerInletTC);
            kerOutletTCvect.push_back(curData.kerOutletTC);
            miscTCvect.push_back(curData.miscTC);

        }

        result.loxVent = data.back().loxVent;
        result.kerVent = data.back().kerVent;
        //result.loxDrip = data.back().loxDrip;
        //result.kerDrip = data.back().kerDrip;

        result.loxPressurant = data.back().loxPressurant;
        result.kerPressurant = data.back().kerPressurant;
        result.loxFlow = data.back().loxFlow;
        result.kerFlow = data.back().kerFlow;
        result.loxPurge = data.back().loxPurge;
        result.kerPurge = data.back().kerPurge;

        result.loxTankDucer = median(loxTankDucervect);
        result.kerTankDucer = median(kerTankDucervect);
        result.purgeDucer = median(purgeDucervect);
        result.loxInletDucer = median(loxInletDucervect);
        result.kerInletDucer = median(kerInletDucervect);
        result.kerPintleDucer = median(kerPintleDucervect);
        result.loxVenturi = median(loxVenturivect);
        result.kerVenturi = median(kerVenturivect);

        result.pneumaticDucer = median(pnematicsDucervect);

        result.loadCell = median(loadCellvect);

        result.loxRegDucer = median(loxRegDucervect);
        result.kerRegDucer = median(kerRegDucervect);
        result.n2pressDucer = median(n2pressDucervect);

        result.loxTankTC = median(loxTankTCvect);
        result.kerInletTC = median(kerInletTCvect);
        result.kerOutletTC = median(kerOutletTCvect);
        result.miscTC = median(miscTCvect);

        return result;
    }
}

/**
 * list out all of the different fields data from the sensordata & commanddata
 * check if all of the test are passing for all of the field cases
 */
SensorData averageData(std::vector<SensorData> data) {
    static_assert(SensorData::majorVersion == 3,
                  "Function not updated from SensorData change, please update this function and the static_assert");
    SensorData outer;
    SensorData result;

    if (data.empty()) {
        return result;
    }

    for (SensorData curData: data) {
        outer.loxTankDucer += curData.loxTankDucer;
        outer.kerTankDucer += curData.kerTankDucer;
        outer.purgeDucer += curData.purgeDucer;
        outer.loxInletDucer += curData.loxInletDucer;
        outer.kerInletDucer += curData.kerInletDucer;
        outer.kerPintleDucer += curData.kerPintleDucer;
        outer.loxVenturi += curData.loxVenturi;
        outer.kerVenturi += curData.kerVenturi;

        outer.pneumaticDucer += curData.pneumaticDucer;

        outer.loadCell += curData.loadCell;

        outer.loxRegDucer += curData.loxRegDucer;
        outer.kerRegDucer += curData.kerRegDucer;
        outer.n2pressDucer += curData.n2pressDucer;

        outer.loxTankTC += curData.loxTankTC;
        outer.kerInletTC += curData.kerInletTC;
        outer.kerOutletTC += curData.kerOutletTC;
        outer.miscTC += curData.miscTC;
    }
    auto datasize = static_cast<float>(data.size());
    result.loxVent = data.back().loxVent;
    result.kerVent = data.back().kerVent;
    result.loxPressurant = data.back().loxPressurant;
    result.kerPressurant = data.back().kerPressurant;
    result.loxFlow = data.back().loxFlow;
    result.kerFlow = data.back().kerFlow;
    result.loxPurge = data.back().loxPurge;
    result.kerPurge = data.back().kerPurge;

    result.loxTankDucer = static_cast<int>(round(static_cast<float>(outer.loxTankDucer) / datasize));
    result.kerTankDucer = static_cast<int>(round(static_cast<float>(outer.kerTankDucer) / datasize));
    result.purgeDucer = static_cast<int>(round(static_cast<float>(outer.purgeDucer) / datasize));
    result.loxInletDucer = static_cast<int>(round(static_cast<float>(outer.loxInletDucer) / datasize));
    result.kerInletDucer = static_cast<int>(round(static_cast<float>(outer.kerInletDucer) / datasize));
    result.kerPintleDucer = static_cast<int>(round(static_cast<float>(outer.kerPintleDucer) / datasize));
    result.loxVenturi = static_cast<int>(round(static_cast<float>(outer.loxVenturi) / datasize));
    result.kerVenturi = static_cast<int>(round(static_cast<float>(outer.kerVenturi) / datasize));

    result.pneumaticDucer = static_cast<int>(round(static_cast<float>(outer.pneumaticDucer) / datasize));

    result.loadCell = static_cast<int>(round(static_cast<float>(outer.loadCell) / datasize));

    result.loxRegDucer = static_cast<int>(round(static_cast<float>(outer.loxRegDucer) / datasize));
    result.kerRegDucer = static_cast<int>(round(static_cast<float>(outer.kerRegDucer) / datasize));
    result.n2pressDucer = static_cast<int>(round(static_cast<float>(outer.n2pressDucer) / datasize));

    result.loxTankTC = static_cast<int>(round(static_cast<float>(outer.loxTankTC) / datasize));
    result.kerInletTC = static_cast<int>(round(static_cast<float>(outer.kerInletTC) / datasize));
    result.kerOutletTC = static_cast<int>(round(static_cast<float>(outer.kerOutletTC) / datasize));
    result.miscTC = static_cast<int>(round(static_cast<float>(outer.miscTC) / datasize));

    return result;

}