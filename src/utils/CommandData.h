//
// Created by kevin on 2/23/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H

#include "ECSUtils.h"
struct SensorData;

/**
 * Class that contains a field for each effector. Represents expected
 * configuration after this command is applied
 *
 * NOTE: the struct definition is AUTO GENERATED by our script
 * (not including the majorVersion)
 */
/**
* The general design and majorVersion numbers deserve deep explanation (because this is arguably a core of our redesign)
* NOTE: I refer to SensorData below, but CommandData follows the same reasoning and design
*
* Fundamentally, we regularly need to change what sensors and effectors we have on our
* ecs software. This is because fundamentally, we need to change which sensors and
* valves we have whenever we change tests
*
* Ex. hotfire, waterflow, coldflow require different sensors and valves, so our software needs
* to reflect that
*
* Our current design favors safety over programmer convenience. This is reasonable considering this
* is a rocket engine.
*
* Consider what if we had a sensor, call it SensorA, but in a new change we don't have it and forget
* to remove its usage in one of functions that directly accesses our SensorData
*
* If we represented SensorData as a map, say from std::string to some data type,
* that means we would do something like data["SensorA"] if we forgot to patch a function, which would be a key
* that no longer exists. This fails at runtime, aka while the program is running. And sure, we could do something
* like catch and throw an exception and delegate it all the way up to the operator to see, but this is a
* pain compared to:
*
* We represent SensorData as a struct, with a field for each sensor.
* Now, when we update our SensorData to remove SensorA, we would remove the SensorA field. If we forget to change a
* function, it would have something like
*  .... data.SensorA ...
* But this program will FAIL TO COMPILE, because it is accessing an invalid field! Thus, we can check for sensor keys
* at COMPILE TIME, and if the program compiles we know we are accessing only valid sensor names.
*
* IF THAT SHIT WAS TOO LONG, TLDR: We make SensorData a struct for compile time guarantees that we are actually accessing
* valid sensors
*
*
* So that's why we have it as a struct. So finally, what is the majorVersion number for?
*
* Well our whole bit above is all about assuring that all sensor accesses are valid. But for some functions, that might
* not be enough, because they need to access EVERY FIELD in SensorData to be considered correct. And our current struct
* set up doesn't catch that, because it's possible that our SensorData change is just adding fields, so no accesses
* are invalidated, but we fail to access these new fields.
*
* For example, the function that parses SensorData back to the operator. If we miss a field, we fail to report that
* value, which is kinda fucked.
*
* So what we do is we bundle a version number with the SensorData definition. And these functions will check the version
* number with a static_assert. static_asserts run at compile time.
*
* The idea is that when we update the SensorData, we will increment its version number. That way, these functions will
* fail to compile. Then we know exactly where to patch. Once we've patched it, we can patch the static_assert. If you're
* still confused, I talked about it a bit on
* https://stackoverflow.com/questions/74309802/compile-time-hints-warnings-on-struct-changes,
* where the question is my initial approach, and the answers suggested this versioning idea to me
*
* SO TLDR AGAIN: We have to increment majorVersion after each struct change. That will make some functions fail to
* compile (which we want!), which we can just patch and go
*/

struct CommandData {
    /**
     * In functions where we want to access all the fields in CommandData, add a
     * static_assert(CommandData::majorVersion == [CURRENT MAJORVERSION VALUE], [ERROR MESSAGE])
     *
     * for safety, as outlined above
     */
    static constexpr int majorVersion = 3;
    CommandData(ECSValveState loxVent_, ECSValveState kerVent_, ECSValveState loxDrip_, ECSValveState kerDrip_, ECSValveState loxPressurant_, ECSValveState kerPressurant_, ECSValveState loxFlow_, ECSValveState kerFlow_, ECSValveState kerOrifice_, ECSValveState loxPurge_, ECSValveState kerPurge_):
            loxVent(loxVent_),
            kerVent(kerVent_),
            loxDrip(loxDrip_),
            kerDrip(kerDrip_),
            loxPressurant(loxPressurant_),
            kerPressurant(kerPressurant_),
            loxFlow(loxFlow_),
            kerFlow(kerFlow_),
            kerOrifice(kerOrifice_),
            loxPurge(loxPurge_),
            kerPurge(kerPurge_){}
    CommandData() = default;
    CommandData(const SensorData &) = delete;
    CommandData &operator=(const SensorData &) = delete;
    ECSValveState loxVent = ECSValveState::INVALID;
    ECSValveState kerVent = ECSValveState::INVALID;
    ECSValveState loxDrip = ECSValveState::INVALID;
    ECSValveState kerDrip = ECSValveState::INVALID;
    ECSValveState loxPressurant = ECSValveState::INVALID;
    ECSValveState kerPressurant = ECSValveState::INVALID;
    ECSValveState loxFlow = ECSValveState::INVALID;
    ECSValveState kerFlow = ECSValveState::INVALID;
    ECSValveState kerOrifice = ECSValveState::INVALID;
    ECSValveState loxPurge = ECSValveState::INVALID;
    ECSValveState kerPurge = ECSValveState::INVALID;
};

bool inline operator==(const CommandData& first, const CommandData second){
    static_assert(CommandData::majorVersion == 2,
                  "Function not updated from CommandData change, please update this function and the static_assert");
    return first.loxVent == second.loxVent
        and first.loxPressurant == second.loxPressurant
        and first.loxFlow == second.loxFlow
        and first.loxPurge == second.loxPurge
        and first.kerVent == second.kerVent
        and first.kerPressurant == second.kerPressurant
        and first.kerFlow == second.kerFlow
        and first.kerPurge == second.kerPurge;
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_COMMANDDATA_H
