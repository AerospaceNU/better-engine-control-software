#include "LabJackSource.h"

#include <cmath>

PropBoardSensorData LabJackSource::getPacket() {
    PropBoardSensorData data{};
    const auto readings = vJack.readAllChannels();

    data.adc0 = static_cast<int32_t>(std::llround(readings[0] * 1000.0));
    data.adc1 = static_cast<int32_t>(std::llround(readings[1] * 1000.0));
    data.adc2 = static_cast<int32_t>(std::llround(readings[2] * 1000.0));
    data.adc3 = static_cast<int32_t>(std::llround(readings[3] * 1000.0));
    data.adc4 = static_cast<int32_t>(std::llround(readings[4] * 1000.0));
    data.adc5 = static_cast<int32_t>(std::llround(readings[5] * 1000.0));
    data.adc6 = static_cast<int32_t>(std::llround(readings[6] * 1000.0));
    data.adc7 = static_cast<int32_t>(std::llround(readings[7] * 1000.0));
    data.adc8 = static_cast<int32_t>(std::llround(readings[8] * 1000.0));
    data.adc9 = static_cast<int32_t>(std::llround(readings[9] * 1000.0));
    data.adc10 = static_cast<int32_t>(std::llround(readings[10] * 1000.0));
    data.adc11 = static_cast<int32_t>(std::llround(readings[11] * 1000.0));
    data.adc12 = static_cast<int32_t>(std::llround(readings[12] * 1000.0));
    data.adc13 = static_cast<int32_t>(std::llround(readings[13] * 1000.0));
    data.adc14 = 0;

    return data;
}