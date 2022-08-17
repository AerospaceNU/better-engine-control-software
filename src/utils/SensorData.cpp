//
// Created by kevin on 8/17/2022.
//

#include "SensorData.h"

SensorData SensorData::applyCalibration(std::array<IntCalibrator*, 16> calibrationArray) {
    SensorData data;

    data.loxTankDucer = calibrationArray[0]->applyCalibration(this->loxTankDucer);
    data.kerTankDucer = calibrationArray[1]->applyCalibration(this->kerTankDucer);
    data.purgeDucer = calibrationArray[2]->applyCalibration(this->purgeDucer);
    data.loxInletDucer = calibrationArray[3]->applyCalibration(this->loxInletDucer);
    data.kerInletDucer = calibrationArray[4]->applyCalibration(this->kerInletDucer);
    data.kerPintleDucer = calibrationArray[5]->applyCalibration(this->kerPintleDucer);
    data.loxVenturi = calibrationArray[6]->applyCalibration(this->loxVenturi);
    data.kerVenturi = calibrationArray[7]->applyCalibration(this->kerVenturi);

    data.pnematicsDucer = calibrationArray[8]->applyCalibration(this->pnematicsDucer);

    data.loadCell = calibrationArray[9]->applyCalibration(this->loadCell);

    data.loxTank1 = calibrationArray[10]->applyCalibration(this->loxTank1);
    data.loxTank2 = calibrationArray[11]->applyCalibration(this->loxTank2);
    data.loxTank3 = calibrationArray[12]->applyCalibration(this->loxTank3);
    data.loxDripLine = calibrationArray[13]->applyCalibration(this->loxDripLine);
    data.outsideThroat = calibrationArray[14]->applyCalibration(this->outsideThroat);
    data.nozzle = calibrationArray[15]->applyCalibration(this->nozzle);

    return data;
}
