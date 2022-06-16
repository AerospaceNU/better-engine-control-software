//
// Created by kevin on 6/15/2022.
//

#include "ECSState.h"

#include <utility>

ECSState::ECSState(std::string name, const std::vector<const IRedline *>& redlines, CommandData *config, const ECSState &failState):
    name(std::move(name)),
    redlines(redlines),
    config(config),
    failState(failState)
{}
