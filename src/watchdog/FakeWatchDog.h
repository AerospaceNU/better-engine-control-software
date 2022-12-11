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
    /**
     * Stores list of initial redlines
     *
     * Filters out null pointers from list
     * @param conds list to store
     */
    explicit FakeWatchDog(std::vector<std::unique_ptr<IRedline>> conds = {});

    void updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) override;

    std::vector<RedlineResponsePacket> stepRedlines(const SensorData& data) override;

private:
    /*
     * INVARIANT: this vector does not contain null pointers
     */
    std::vector<std::unique_ptr<IRedline>> conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
