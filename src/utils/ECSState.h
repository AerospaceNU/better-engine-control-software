//
// Created by kevin on 5/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H

#include <string>
#include <vector>
#include "watchdog/redlines/IRedline.h"
#include "CommandData.h"

/**
 * Represents a pre-defined state for the ECS to transition to
 */
class ECSState{
public:

    ECSState(std::string name, std::vector<std::unique_ptr<IRedline>> redlines, CommandData config, CommandData failState);
    ~ECSState() = default;

    ECSState(const ECSState& other);
    ECSState(ECSState&& other) = default;
    ECSState& operator=(ECSState other);

    /**
     * Get name of this state
     * @return name
     */
    [[nodiscard]] std::string getName() const;

    /**
     * Get redlines for this state
     * @return redlines
     */
    [[nodiscard]] std::vector<std::unique_ptr<IRedline>> getRedlines() const;

    /**
     * Get CommandData for this state
     * @return state config
     */
    [[nodiscard]] CommandData getConfig() const;

    /**
     * Get config of abort from this state
     * @return abort config
     */
    [[nodiscard]] CommandData getFailState() const;

private:
    std::string name;
    std::vector<std::unique_ptr<IRedline>> redlines;
    CommandData config;
    CommandData failState;

    /**
     * helper function for assignment operator
     * @param left
     * @param right
     */
    friend void swap(ECSState& left, ECSState& right) noexcept;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ISTATE_H
