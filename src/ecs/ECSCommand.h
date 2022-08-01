//
// Created by kevin on 7/31/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ECSCOMMAND_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ECSCOMMAND_H

class HorizontalECS;

struct ECSCommand {
    virtual void applyCommand(HorizontalECS& ecs) = 0;

    virtual ~ECSCommand() = default;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ECSCOMMAND_H
