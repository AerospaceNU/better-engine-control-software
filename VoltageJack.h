#pragma once

#include <LabJackM.h>

#include <array>
#include <cstddef>

class VoltageJack {
public:
    static constexpr std::size_t kTotalChannelCount = 14;

    struct ChannelConfig {
        const char* name;
        double scale;
        double offset;
        bool isCurrent;
    };

    VoltageJack();
    ~VoltageJack();

    [[nodiscard]] int getHandle() const;
    [[nodiscard]] std::array<double, kTotalChannelCount> readAllChannels();

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
    [[nodiscard]] double getCurrentAIN13() const;
    [[nodiscard]] double getAmpsAIN14() const;

private:
    static constexpr std::array<ChannelConfig, kTotalChannelCount> kDefaultChannels{{
        {"AIN0", 1.0, 0.0, false},
        {"AIN1", 1.0, 0.0, false},
        {"AIN2", 1.0, 0.0, false},
        {"AIN3", 1.0, 0.0, false},
        {"AIN4", 1.0, 0.0, false},
        {"AIN5", 1.0, 0.0, false},
        {"AIN6", 1.0, 0.0, false},
        {"AIN7", 1.0, 0.0, false},
        {"AIN8", 1.0, 0.0, false},
        {"AIN9", 1.0, 0.0, false},
        {"AIN10", 1.0, 0.0, false},
        {"AIN11", 1.0, 0.0, false},
        {"AIN12", 1.0, 0.0, false},
        {"AIN13", 1.0, 0.0, true}
    }};

    void refreshChannels();

    int error;
    int handle;
    char ErrorString[LJM_MAX_NAME_SIZE]{};
    double Value = 0.0;
    int LJMError = 0;
    std::array<double, kTotalChannelCount> channelValues{};
};