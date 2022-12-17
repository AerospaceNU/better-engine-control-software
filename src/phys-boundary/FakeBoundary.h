#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

#include "IPhysicalBoundary.h"

/**
 * Boundary used in the sim. Can also be used for unit testing
 *
 * Will report random sensor readings, but should apply actual commands
 * correctly
 */
class FakeBoundary : public IPhysicalBoundary{
public:
    /**
     * Initializes stored data in boundary, specifically
     * the valve fields to CLOSED state
     */
    FakeBoundary();
    SensorData readFromBoundary() override;

    /**
     * Sets the stored data to the given configuration
     * @param data command data representing the configuration we want
     * @throws EffectorException if writing fails (valves don't work, etc)
     */
    void writeToBoundary(const CommandData& data) override;
private:
    SensorData curData;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEBOUNDARY_H

