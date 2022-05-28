//
// Created by kevin on 5/27/2022.
//

#include "utils-and-constants/ECSUtils.h"

uint64_t getTimeStamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    ).count();
}