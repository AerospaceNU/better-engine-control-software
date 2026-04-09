#include "LabJackSource.h"

//we need for main labj to read the voltages from the labjack, so we
 //need to implement the getPacket function to do that. This is where we will read the voltages from the labjack and convert them to the format of PropBoardSensorData
PropBoardSensorData LabJackSource::getPacket() {
    PropBoardSensorData data;

    //read voltages from labjack and store in data
    data.adc0 = vJack.getHandle();
    data.adc1 = vJack.getVoltageAINO();
    data.adc2 = vJack.getVoltageAINOne();
    data.adc3 = vJack.getVoltageAINTwo();
    data.adc4 = vJack.getVoltageAIN3();
    data.adc5 = vJack.getAmpsAIN4();
    //add more as needed
    return data;
}