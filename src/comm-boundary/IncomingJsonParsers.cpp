//
// Created by kevin on 12/20/2022.
//

#include "IncomingJsonParsers.h"
#include "ParsingHelpers.h"
#include <stdexcept>

void parseStartSequenceCommand(const json& message, IECS& ecs){
    std::string desiredSequence;
    try {
        desiredSequence = message.at("sequence");
    }
    catch(json::exception&){
        throw std::invalid_argument{"Bad json read on sequence start, 'sequence' tag not found"};
    }

    try{
        ecs.acceptStartSequence(stringToSequence(desiredSequence));
    }
    catch (std::invalid_argument&){
        std::string msg;
        msg += "Requested sequence: [";
        msg += desiredSequence + "] ";
        msg += "is not a valid sequence";

        throw std::invalid_argument{msg};
    }
}

void parseAbortSequenceCommand([[maybe_unused]] const json& command, IECS& ecs){
    ecs.acceptAbortSequence();
}

void parseOverrideCommand(const json& message, IECS& ecs){
    try {
        /*
         * This section of code should hit all the fields
         * in CommandData
         */
        static_assert(CommandData::majorVersion == 2,
                      "Function not updated from CommandData change, please update this function and the static_assert");

        CommandData newOverrideCom;
        json overrideElements = message.at("activeElements");

        newOverrideCom.loxPressurant = stringToValveState(overrideElements.at("loxPressurant"));
        newOverrideCom.kerPressurant = stringToValveState(overrideElements.at("kerPressurant"));

        newOverrideCom.loxPurge = stringToValveState(overrideElements.at("loxPurge"));
        newOverrideCom.kerPurge = stringToValveState(overrideElements.at("kerPurge"));

        newOverrideCom.loxVent = stringToValveState(overrideElements.at("loxVent"));
        newOverrideCom.kerVent = stringToValveState(overrideElements.at("kerVent"));

        newOverrideCom.loxFlow = stringToValveState(overrideElements.at("loxFlow"));
        newOverrideCom.kerFlow = stringToValveState(overrideElements.at("kerFlow"));

        ecs.acceptOverrideCommand(newOverrideCom);
    }
    catch (json::exception&) {
        throw std::invalid_argument{"Failed parse from JSON data to CommandData on manual override, missing field?"};
    }
    catch (std::invalid_argument&) {
        throw std::invalid_argument{"Invalid valve state from manual override command!"};
    }
}

void parseStateCommand(const json& message, IECS& ecs){
    std::string newStateCommand;

    try {
        newStateCommand = message.at("newState");
    }
    catch(json::exception&){
        throw std::invalid_argument{"Bad json read on state transition, 'newState' tag not found"};
    }

    try {
        ecs.acceptStateTransition(stringToECSState(newStateCommand));
    }
    catch (std::invalid_argument&){
        std::string msg;
        msg += "Requested state: [";
        msg += newStateCommand + "] ";
        msg += "is not a valid state";

        throw std::invalid_argument{msg};
    }
}