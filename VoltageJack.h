#pragma once

#include <LabJackM.h>

class VoltageJack {
private:
    int error;
    int handle;
    char ErrorString[LJM_MAX_NAME_SIZE]{};
    double Value = 0;
    //gets our library version, not used but good for testing connection
    int LJMError;
    double volt0; // handles our voltage
    double volt1{};
    double volt2{};
    double volt3{};
    //amps
    double amp1{};

public:
    // Constructor
    VoltageJack();
    [[nodiscard]] int getHandle() const;
    [[nodiscard]] double getVoltageAINO() const;
    [[nodiscard]] double getVoltageAINOne() const;
    [[nodiscard]] double getVoltageAINTwo() const;
    [[nodiscard]] double getVoltageAIN3() const;
    //use one output for amp - should have 7 since t7
    [[nodiscard]] double getAmpsAIN4() const;
    //goes up to 7 with T7 I believe. based off docs
    ~VoltageJack();
};