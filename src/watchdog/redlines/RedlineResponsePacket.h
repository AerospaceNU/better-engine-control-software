//
// Created by kevin on 12/8/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_REDLINERESPONSEPACKET_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_REDLINERESPONSEPACKET_H

#include "utils/ECSUtils.h"
#include <string>

/**
 * Struct that contains all the data needed to report the results of a redline
 *
 * Includes actual enum response, as well as name of redline
 */
struct RedlineResponsePacket {
    RedlineResponsePacket(ECSRedLineResponse response, std::string redlineName);

    ECSRedLineResponse response;
    std::string redlineName;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_REDLINERESPONSEPACKET_H
