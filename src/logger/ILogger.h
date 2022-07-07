//
// Created by kevin on 6/8/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ILOGGER_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ILOGGER_H

#include <string>

class ILogger{
public:
    void getAllContents();
    void logSensorData(SensorData* data, uint16_t time);
    void logFailedRedline(Redline* redline, uint16_t time);
    void logECSTransition(ECSState* ecstate, uint16_t time);
    void logValveCommand(CommandData* cmd, uint16_t time);
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ILOGGER_H
