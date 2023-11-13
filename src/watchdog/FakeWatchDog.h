#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H

#include "IWatchDog.h"
#include <etl/vector.h>

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
     * 30 REDLINES, 15 EXTRA FOR WARNINGS AND ABORTS
     * @param conds list to store
     */
    explicit FakeWatchDog(etl::vector<std::unique_ptr<IRedline>, 45> conds = {});

    void updateRedlines(etl::vector<std::unique_ptr<IRedline>, 45> newRedlines) override;

    etl::vector<RedlineResponsePacket, 45> stepRedlines(const SensorData& data) override;

private:
    /*
     * INVARIANT: this vector does not contain null pointers
     */
    etl::vector<std::unique_ptr<IRedline>, 45> conditions;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEWATCHDOG_H
