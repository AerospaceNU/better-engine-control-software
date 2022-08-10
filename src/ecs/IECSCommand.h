//
// Created by kevin on 7/31/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IECSCOMMAND_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IECSCOMMAND_H

class HorizontalECS;

/**
 * Abstract object for the command design pattern that will apply a change to the ECS
 */
struct IECSCommand {
    /**
     * Apply method
     * @param ecs ecs to apply to
     */
    virtual void applyCommand(HorizontalECS& ecs) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IECSCommand() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IECSCOMMAND_H
