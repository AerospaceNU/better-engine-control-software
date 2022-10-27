#include <cmath>
#include "SensorDataUtils.h"

SensorData averageData(std::vector<SensorData> data) {
    SensorData outer;
    SensorData result;
    if (data.size() == 0) {
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