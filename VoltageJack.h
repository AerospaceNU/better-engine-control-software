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
    //changed from O, one, two, three naming conventions to num
    [[nodiscard]] double getVoltageAIN0() const;
    [[nodiscard]] double getVoltageAIN1() const;
    [[nodiscard]] double getVoltageAIN2() const;
    [[nodiscard]] double getVoltageAIN3() const;
    [[nodiscard]] double getVoltageAIN4() const;

    [[nodiscard]] double getVoltageAIN5() const;
    [[nodiscard]] double getVoltageAIN6() const;
    [[nodiscard]] double getVoltageAIN7() const;
    [[nodiscard]] double getVoltageAIN8() const;
    [[nodiscard]] double getVoltageAIN9() const;
    [[nodiscard]] double getVoltageAIN10() const;
    [[nodiscard]] double getVoltageAIN11() const;
    [[nodiscard]] double getVoltageAIN12() const;
    [[nodiscard]] double getVoltageAIN13() const;
    //use one output for amp - should have 7 since t7
    [[nodiscard]] double getAmpsAIN4() const;
    //goes up to 7 with T7 I believe. based off docs
    ~VoltageJack();
};