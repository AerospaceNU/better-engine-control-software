//
// Created by Jack Hester on 6/11/2022.
//
#include "Logger.h"

Logger::Logger():
    fileObject()
{}

Logger::Logger(const std::string& csv_name):
    fileObject(csv_name)
{}

void Logger::write(const std::string& str) {
    if(this->fileObject.is_open()) {
        this->fileObject << str << "\n";
    }
}



