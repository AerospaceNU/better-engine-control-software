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
    /*
     * All ECSStates are initialized on startup. If we ever need to create new
     * ECSStates during the runtime of the program, then we will need to revisit
     * all the places we store pointers/references to ECSStates to make sure they
     * stay valid
     *
     * TLDR: DO NOT DO NOT DO NOT DO NOT DO NOT CONSTRUCT AN ECSSTATE AT RUNTIME
     */
    ECSState(std::string name, std::vector<std::unique_ptr<IRedline>> redlines, CommandData config, CommandData failState);

    ~ECSState() = default;
    /*
     * deleting the copy/move constructors that way we don't accidently make new ECSStates
     */
    ECSState(const ECSState& other);
    ECSState(ECSState&& other) = default;
    ECSState& operator=(ECSState other);



    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::vector<std::unique_ptr<IRedline>> getRedlines() const;
    [[nodiscard]] CommandData getConfig() const;
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
