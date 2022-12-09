//
// Created by kevin on 10/19/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_IECSHIGHCOMMAND_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_IECSHIGHCOMMAND_H

class StandECS;

/**
 * Abstract object for the command design pattern that will apply a change to the ECS
 *
 * This is for commands that are higher priority than other commands (ex. aborts)
 */
struct IECSHighCommand {
    /**
     * Apply method
     * @param ecs ecs to apply to
     */
    virtual void applyHighCommand(StandECS& ecs) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IECSHighCommand() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_IECSHIGHCOMMAND_H
