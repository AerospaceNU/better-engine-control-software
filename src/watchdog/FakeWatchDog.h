#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H

#include "IWatchDog.h"

/**
 * An implementation of WatchDog without any filtering
 *
 * This means this object will run redlines directly on the passed SensorData
 * without storing any others and computing a median/mean
 *
 * Useful for unit testing
 */
class FakeWatchDog: public IWatchDog{
public:
    explicit FakeWatchDog(std::vector<std::unique_ptr<IRedline>> conds = {});

    void updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) override;

    std::vector<RedlineResponsePacket> stepRedlines(SensorData& data) override;

private:
    std::vector<std::unique_ptr<IRedline>> conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
