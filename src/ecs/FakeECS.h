//
// Created by kevin on 9/29/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEECS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEECS_H

#include "IECS.h"

class FakeECS: public IECS {
    void acceptStartSequence(ISequence& seq) override;
    void acceptStateTransition(ECSState& newState) override;
    void acceptOverrideCommand(CommandData commands) override;
    void acceptAbortSequence() override;
    void acceptAbort() override;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEECS_H
