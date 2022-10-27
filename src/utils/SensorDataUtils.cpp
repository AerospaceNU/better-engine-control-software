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

SensorData medianData(std::vector<SensorData> data) {
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

            pnematicsDucervect.push_back(curData.pnematicsDucer);

            loadCellvect.push_back(curData.loadCell);
        }

        result.loxVent = data.back().loxVent;
        result.kerVent = data.back().kerVent;
        result.loxDrip = data.back().loxDrip;
        result.kerDrip = data.back().kerDrip;
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

        result.pnematicsDucer = median(pnematicsDucervect);

        result.loadCell = median(loadCellvect);

        return result;
    }
}


SensorData averageData(std::vector<SensorData> data) {
    SensorData outer;
    SensorData result;

    if (data.empty()) {
        return result;
    } else {


        for (SensorData curData: data) {
            outer.loxTankDucer += curData.loxTankDucer;
            outer.kerTankDucer += curData.kerTankDucer;
            outer.purgeDucer += curData.purgeDucer;
            outer.loxInletDucer += curData.loxInletDucer;
            outer.kerInletDucer += curData.kerInletDucer;
            outer.kerPintleDucer += curData.kerPintleDucer;
            outer.loxVenturi += curData.loxVenturi;
            outer.kerVenturi += curData.kerVenturi;

            outer.pnematicsDucer += curData.pnematicsDucer;

            outer.loadCell += curData.loadCell;
        }
        float datasize = data.size();
        result.loxVent = data.back().loxVent;
        result.kerVent = data.back().kerVent;
        result.loxDrip = data.back().loxDrip;
        result.kerDrip = data.back().kerDrip;
        result.loxPressurant = data.back().loxPressurant;
        result.kerPressurant = data.back().kerPressurant;
        result.loxFlow = data.back().loxFlow;
        result.kerFlow = data.back().kerFlow;
        result.loxPurge = data.back().loxPurge;
        result.kerPurge = data.back().kerPurge;

        result.loxTankDucer = round((outer.loxTankDucer) / datasize);
        result.kerTankDucer = round((outer.kerTankDucer) / datasize);
        result.purgeDucer = round((outer.purgeDucer) / datasize);
        result.loxInletDucer = round((outer.loxInletDucer) / datasize);
        result.kerInletDucer = round((outer.kerInletDucer) / datasize);
        result.kerPintleDucer = round((outer.kerPintleDucer) / datasize);
        result.loxVenturi = round((outer.loxVenturi) / datasize);
        result.kerVenturi = round((outer.kerVenturi) / datasize);

        result.pnematicsDucer = round((outer.pnematicsDucer) / datasize);

        result.loadCell = round((outer.loadCell) / datasize);

        return result;
    }
}