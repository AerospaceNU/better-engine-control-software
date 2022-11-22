//
// Created by kevin on 6/17/2022.
//

#include "TeensyBoundary.h"
#include <utility>

namespace{
    void updateFromPropBoard(SensorData& data, PropBoardSensorData& propPacket){
        static_assert(SensorData::majorVersion == 1,
                      "Function not updated from SensorData change, please update this function and the static_assert");
        //TODO will likely require sensordata changes, update later
    }
}


TeensyBoundary::TeensyBoundary(std::unique_ptr<IECSValve> loxPressurant_, std::unique_ptr<IECSValve> kerPressurant_,
                               std::unique_ptr<IECSValve> loxPurge_, std::unique_ptr<IECSValve> kerPurge_,
                               std::unique_ptr<IECSValve> loxVent_, std::unique_ptr<IECSValve> kerVent_,
                               std::unique_ptr<IECSValve> loxFlow_, std::unique_ptr<IECSValve> kerFlow_,
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
        loxDrip(std::move(loxDrip_)),
        kerDrip(std::move(kerDrip_)),
        packetSource(std::move(pSource)),
        calibratorList(std::move(cList))
{
    static_assert(CommandData::majorVersion == 1,
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

void TeensyBoundary::writeToBoundary(CommandData &data) {
    static_assert(CommandData::majorVersion == 1,
                  "Function not updated from CommandData change, please update this function and the static_assert");

    this->loxVent->setValveState(data.loxVent);
    this->kerVent->setValveState(data.kerVent);

    this->loxDrip->setValveState(data.loxDrip);
    this->kerDrip->setValveState(data.kerDrip);

    this->loxPressurant->setValveState(data.loxPressurant);
    this->kerPressurant->setValveState(data.kerPressurant);

    this->loxFlow->setValveState(data.loxFlow);
    this->kerFlow->setValveState(data.kerFlow);

    this->loxPurge->setValveState(data.loxPurge);
    this->kerPurge->setValveState(data.kerPurge);
}


void TeensyBoundary::readFromEffectors(SensorData& storedData) {
    static_assert(CommandData::majorVersion == 1,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    storedData.loxVent = this->loxVent->getValveState();
    storedData.kerVent = this->kerVent->getValveState();
    storedData.loxDrip = this->loxDrip->getValveState();
    storedData.kerDrip = this->kerDrip->getValveState();
    storedData.loxPressurant = this->loxPressurant->getValveState();
    storedData.kerPressurant = this->kerPressurant->getValveState();
    storedData.loxFlow = this->loxFlow->getValveState();
    storedData.kerFlow = this->kerFlow->getValveState();
    storedData.loxPurge = this->loxPurge->getValveState();
    storedData.kerPurge = this->kerPurge->getValveState();
}




