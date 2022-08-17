//
// Created by kevin on 5/27/2022.
//

#include "ECSUtils.h"
#include <cmath>

/*
 * convert state boolean (true or false) to string of open or closed
 * @return state_str a string of the state (open or closed)
 * here, true is open and false is closed
*/
std::string bool_to_str(bool state){
    std::string state_str;
    if(state==false){
        state_str = "closed";
    } else if(state==true){
        state_str = "open";
    }/* else{
                std::cout << errors::INVALID_PARAM_ERROR << std::endl;
                //state_str = null;
            }*/
    return state_str;
}

/*
 * get_date()
 * @return date_str, a string with the current date in the format of YYYY-(M)M-(D)D_(H)H-(M)M-(S)S e.g., 2022-6-13_15-4-6
 */
std::string get_date(){

    time_t now = time(0);
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

/*
 * get_posix()
 * @returns a long int of the posix (i.e., epoch, unix) time in 16 digit form
 * if converted can get GMT time and/or time in current timezone
 */
unsigned long int get_posix(){

    const auto p1 = std::chrono::system_clock::now();
    return (posixLong) abs(p1.time_since_epoch().count()); // epoch seconds

}

uint64_t getTimeStamp() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
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