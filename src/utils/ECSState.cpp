//
// Created by kevin on 6/15/2022.
//

#include "ECSState.h"

#include <utility>
#include <etl/vector.h>

void swap(ECSState& left, ECSState& right) noexcept {
    using std::swap;

    swap(left.name, right.name);
    swap(left.redlines, right.redlines);
    swap(left.config, right.config);
    swap(left.failState, right.failState);
}

ECSState::ECSState(std::string name_,
                   std::vector<std::unique_ptr<IRedline>> redlines_,
                   CommandData config_,
                   CommandData failState_):
    name(std::move(name_)),
    redlines(std::move(redlines_)),
    config(config_),
    failState(failState_)
{}

ECSState::ECSState(const ECSState &other):
    name(other.name),
    redlines(other.getRedlines()),
    config(other.config),
    failState(other.failState)
{}

ECSState& ECSState::operator=(ECSState other) {
    swap(*this, other);

    return *this;
}

std::string ECSState::getName() const {
    return this->name;
}

etl::vector<std::unique_ptr<IRedline>, 45> ECSState::getRedlines() const {
    etl::vector<std::unique_ptr<IRedline>, 45> result;

    for (auto& elem: this->redlines){
        result.emplace_back(elem->clone());
    }
    return result;
}

CommandData ECSState::getConfig() const {
    return this->config;
}

CommandData ECSState::getFailState() const {
    return this->failState;
}


