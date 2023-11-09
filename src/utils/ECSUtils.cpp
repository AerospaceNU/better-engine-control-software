//
// Created by kevin on 5/27/2022.
//
/*
 * Gets rid of deprecation warning on localtime for MSVC compiler
 *
 * It would be better to fix it, but its a enormous fucking pain bc of
 * Microsoft being dumb
 *
 * We only use it once really, so I'm fine with just leaving it and turning
 * off the warning
 */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "ECSUtils.h"
#include <cmath>


/*
 * get_date()
 * @return date_str, a string with the current date in the format of YYYY-(M)M-(D)D_(H)H-(M)M-(S)S e.g., 2022-6-13_15-4-6
 */
std::string get_date(){

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);

    int year = ltm->tm_year + 1900;
    int month = ltm->tm_mon + 1;
    int day = ltm->tm_mday;

    int hour = ltm->tm_hour;
    int minute = ltm->tm_min;
    int second = ltm->tm_sec;

    std::string date_str = std::to_string(year)+"-"+std::to_string(month)+"-"+std::to_string(day)+"_"+ std::to_string(hour)+"-"+ std::to_string(minute)+ "-"+ std::to_string(second);

    return date_str;
}


uint64_t getTimeStamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}


/*
 * filterDoubleNan
 * checks if an expected double is NaN, if so sets it to 0
 * @param check, double to check if it's NaN or not
 */
double filterDoubleNan(double check) {
    if (std::isnan(check)) {
        return 0;
    } else {
        return check;
    }
}

#ifdef _MSC_VER
#undef _CRT_SECURE_NO_WARNINGS
#endif
