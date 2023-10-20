//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include <utility>

namespace{
    /*
     * Currently, we only have one data packet that contains all our sensordata,
     * so this function should hit all the sensor fields (so non-effector fields) in SensorData
     */
    void updateFromPropBoard(SensorData& data, PropBoardSensorData& propPacket){
        static_assert(SensorData::majorVersion == 5,
                      "Function not updated from SensorData change, please update this function and the static_assert");

        data.loadCell = propPacket.loadCellRaw;

        data.boardTemp = propPacket.tcInternalTemp;

        data.loxTankDucer = propPacket.adc0;
        data.kerTankDucer = propPacket.adc10; //TODO: 10 is orifice ducer

        data.loxRegDucer = propPacket.adc5;
        data.kerRegDucer = propPacket.adc2;

        data.n2pressDucer = propPacket.adc12;

        data.loxVenturi = propPacket.adc1;
        data.loxVenturi2 = propPacket.adc10;
        data.kerVenturi = propPacket.adc6;
        data.kerVenturi2 = propPacket.adc8;

        data.purgeDucer = propPacket.adc7;
        data.pneumaticDucer = propPacket.adc14;

        data.kerInletDucer = propPacket.adc12;
        data.kerPintleDucer = propPacket.adc11;
        data.loxInletDucer = propPacket.adc13;

        data.kerInletTC = propPacket.tcTemp1;
        data.kerOutletTC = propPacket.tcTemp2;
        data.loxTankTC = propPacket.tcTemp3;
        data.miscTC = propPacket.tcTemp4;

        data.kerInletTC_Fault = propPacket.tcFaultFlags[0];
        data.kerOutletTC_Fault = propPacket.tcFaultFlags[1];
        data.loxTankTC_Fault = propPacket.tcFaultFlags[2];
        data.miscTC_Fault = propPacket.tcFaultFlags[3];
    }
}


TeensyBoundary::TeensyBoundary(std::unique_ptr<IECSValve> loxPressurant_, std::unique_ptr<IECSValve> kerPressurant_,
                               std::unique_ptr<IECSValve> loxPurge_, std::unique_ptr<IECSValve> kerPurge_,
                               std::unique_ptr<IECSValve> loxVent_, std::unique_ptr<IECSValve> kerVent_,
                               std::unique_ptr<IECSValve> loxFlow_, std::unique_ptr<IECSValve> kerFlow_,
                               std::unique_ptr<IECSValve> kerOrifice_,
                               std::unique_ptr<IECSValve> loxDrip_, std::unique_ptr<IECSValve> kerDrip_,
                               std::unique_ptr<IPacketSource<PropBoardSensorData>> pSource,
                               std::vector<SensorDataCalibrator> cList):
        loxPressurant(std::move(loxPressurant_)),
        kerPressurant(std::move(kerPressurant_)),
        loxPurge(std::move(loxPurge_)),
        kerPurge(std::move(kerPurge_)),
        loxVent(std::move(loxVent_)),
        kerVent(std::move(kerVent_)),
        loxFlow(std::move(loxFlow_)),
        kerFlow(std::move(kerFlow_)),
        kerOrifice(std::move(kerOrifice_)),
        loxDrip(std::move(loxDrip_)),
        kerDrip(std::move(kerDrip_)),
        packetSource(std::move(pSource)),
        calibratorList(std::move(cList))
{
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
}

SensorData TeensyBoundary::readFromBoundary() {
    SensorData data;

    PropBoardSensorData pData = this->packetSource->getPacket();
    updateFromPropBoard(data, pData);

    this->readFromEffectors(data);

    for(auto& calibrator: this->calibratorList){
        calibrator.applyCalibration(data);
    }

    return data;
}

/*
 * this function should hit all the fields in CommandData
 */
void TeensyBoundary::writeToBoundary(const CommandData &data) {
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");

    this->loxVent->setValveState(data.loxVent);
    this->kerVent->setValveState(data.kerVent);

    this->loxPressurant->setValveState(data.loxPressurant);
    this->kerPressurant->setValveState(data.kerPressurant);

    this->loxFlow->setValveState(data.loxFlow);
    this->kerFlow->setValveState(data.kerFlow);

    this->loxPurge->setValveState(data.loxPurge);
    this->kerPurge->setValveState(data.kerPurge);

    this->kerOrifice->setValveState(data.kerOrifice);

    this->loxDrip->setValveState(data.loxDrip);
    this->kerDrip->setValveState(data.kerDrip);
}

/*
 * This function should hit all the effector fields in SensorData
 */
void TeensyBoundary::readFromEffectors(SensorData& storedData) {
    static_assert(CommandData::majorVersion == 4,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    storedData.loxVent = this->loxVent->getValveState();
    storedData.kerVent = this->kerVent->getValveState();
    storedData.loxPressurant = this->loxPressurant->getValveState();
    storedData.kerPressurant = this->kerPressurant->getValveState();
    storedData.loxFlow = this->loxFlow->getValveState();
    storedData.kerFlow = this->kerFlow->getValveState();
    storedData.loxPurge = this->loxPurge->getValveState();
    storedData.kerPurge = this->kerPurge->getValveState();
    storedData.kerOrifice = this->kerOrifice->getValveState();
    storedData.loxDrip = this->loxDrip->getValveState();
    storedData.kerDrip = this->kerDrip->getValveState();
}




