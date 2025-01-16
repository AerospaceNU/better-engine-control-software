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
    void updateFromPropBoard(SensorData& data, const PropBoardSensorData& propPacket){
        static_assert(SensorData::majorVersion == 8,
                      "Function not updated from SensorData change, please update this function and the static_assert");

        data.loadCell = propPacket.loadCellRaw; //DONE

        data.boardTemp = propPacket.tcInternalTemp;

        data.orificeDownstreamDucer = propPacket.adc13; //DONE
        // data.kerTankDucer = propPacket.adc10; //NOT USED

        data.loxRegDucer = propPacket.adc5; //DONE
        data.kerRegDucer = propPacket.adc1; //DONE

        // data.n2pressDucer = propPacket.adc12; //NOT USED

        data.loxVenturi = propPacket.adc4; //DONE
        data.loxVenturi2 = propPacket.adc3; //DONE
        data.kerVenturi = propPacket.adc6; //DONE
        data.kerVenturi2 = propPacket.adc9; //DONE

        // data.purgeDucer = propPacket.adc7; //NOT USED
        data.pneumaticDucer = propPacket.adc10; //DONE

        data.kerInletDucer = 0; // ??
        data.kerPintleDucer = propPacket.adc11; //DONE
        // data.loxInletDucer = propPacket.adc13; //NOT USED

        data.orificeUpstreamDucer = propPacket.adc2; //DONE

        data.loxTankDucer = propPacket.adc0; //added
        data.loxFlowDucer = propPacket.adc8; //added
        data.n2pressDucer = propPacket.adc7; //added

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

    const PropBoardSensorData pData = this->packetSource->getPacket();
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





