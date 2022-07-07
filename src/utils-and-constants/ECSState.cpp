//
// Created by kevin on 6/15/2022.
//

#include "utils-and-constants/ECSState.h"

#include <utility>

ECSState::ECSState(std::string name, std::vector<IRedline *>& redlines, CommandData *config, ECSState &failState):
    name(std::move(name)),
    redlines(redlines),
    config(config),
    failState(failState)
{}
