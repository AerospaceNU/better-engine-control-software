#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_LABJACKSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_LABJACKSOURCE_H

#include "PiUtils.h"  // for PropBoardSensorData and WrappedPacket
#include "IPacketSource.h"
#include "VoltageJack.h"

class LabJackSource : public IPacketSource<PropBoardSensorData> {
private:
    VoltageJack& vJack;
    
public:
    explicit LabJackSource(VoltageJack& jack) : vJack(jack) {}

    PropBoardSensorData getPacket() override;

    
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_LABJACKSOURCE_H