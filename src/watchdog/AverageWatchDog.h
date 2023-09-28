#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H

#include "IWatchDog.h"
#include <deque>

/**
 * An implementation of WatchDog with filtering
 *
 * This object will run redlines on the passed SensorData,
 * storing and computing a median/mean.
 *
 * Useful for unit testing
 */
class AverageWatchDog: public IWatchDog{
public:
    /**
     * Stores list of initial redlines
     *
     * Filters out null pointers from list
     * @param conds list to store
     */
    explicit AverageWatchDog(std::vector<std::unique_ptr<IRedline>> conds = {});

    void updateRedlines(std::vector<std::unique_ptr<IRedline>> newRedlines) override;

    std::vector<RedlineResponsePacket> stepRedlines(const SensorData& data) override;

private:
    /*
     * INVARIANT: this vector does not contain null pointers
     */
    std::vector<std::unique_ptr<IRedline>> conditions;
    std::deque<SensorData> dataHistory;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
