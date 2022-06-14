//
// Created by Jack Hester on 6/13/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_UTILS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_UTILS_H

#include <ctime>
#include <string>

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
                std::cout << INVALID_PARAM_ERROR << std::endl;
                //state_str = null;
            }*/
    return state_str;
};

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
double get_posix(){

    const auto p1 = std::chrono::system_clock::now();
    return (long int) abs(p1.time_since_epoch().count()); // epoch seconds

}


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_UTILS_H
