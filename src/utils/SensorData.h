#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H

#include "ECSUtils.h"
#include <array>
#include "CommandData.h"

/**
 * Class that contains a field for each sensor and readable effector with their data
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
struct SensorData: public CommandData {
    /**
     * In functions where we want to access all the fields in SensorData, add a
     * static_assert(SensorData::majorVersion == [CURRENT MAJORVERSION VALUE], [ERROR MESSAGE])
     *
     * for safety, as outlined above
     */
    static constexpr int majorVersion = 4;

    int loxTankDucer = 0;
    int kerTankDucer = 0;
    int purgeDucer = 0;
    int loxInletDucer = 0;
    int kerInletDucer = 0;
    int kerPintleDucer = 0;
    int loxVenturi = 0;
    int kerVenturi = 0;
    int loadCell = 0;
    int pneumaticDucer = 0;
    int loxRegDucer = 0;
    int kerRegDucer = 0;
    int n2pressDucer = 0;
    int loxTankTC = 0;
    int kerInletTC = 0;
    int kerOutletTC = 0;
    int miscTC = 0;
    int boardTemp = 0;

    uint8_t kerInletTC_Fault = 0;
    uint8_t kerOutletTC_Fault = 0;
    uint8_t loxTankTC_Fault = 0;
    uint8_t miscTC_Fault = 0;
};

/*
 * this operator is deleted for a devious little reason
 *
 * we implement a CommandData == operator
 *
 * SensorData extends CommandData, which is useful to use the
 * CommandData == operator when comparing a SensorData from a certain config
 * represented by CommandData (see: our unit tests)
 *
 * However, the CommandData == operator will also SILENTLY accept
 * SensorData == SensorData, which is a bit risky because the CommandData
 * == obviously doesn't compare all the fields in SensorData
 *
 * So TDLR, we have a CommandData == which we want it to accept
 * a CommandData and a CommandData
 * a SensorData and a CommandData
 * a CommandData and a SensorData
 *
 * but not
 * SensorData and SensorData
 *
 * so we delete this operator explicitly
 *
 * we can just implement this operator== for SensorData later if we want,
 * but we just need to make sure the CommandData one doesn't randomly eat
 * SensorDatas when we aren't expecting it to
 */
bool operator==(SensorData& left, SensorData right) = delete;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATA_H
