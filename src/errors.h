//
// Created by Jack Hester on 6/13/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ERRORS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ERRORS_H

//define a list of error messages that will be shared throughout the ECS code
//these values cannot be re-defined elsewhere for consistency
//this should be included in ALL files!

#include <string>

const std::string LOGGING_ERORR = "[-] ERROR: Logging of value(s) failed";
const std::string FILE_NOT_FOUND_ERROR = "[-] ERROR: File not found";
const std::string SOCKET_ERROR = "[-] ERROR: Socket error";
const std::string INVALID_PARAM_ERROR = "[-] ERROR: Invalid parameter provided to function";

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ERRORS_H
