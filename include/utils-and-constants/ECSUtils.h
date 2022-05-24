#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H

enum ECSValveState {
    OPEN,
    CLOSED,
    INVALID
};

enum ECSRedLineResponse{
    ABORT,
    WARN
};

enum ECSMessageType{
    ERROR,
    SENSORDATA,
    LOG
};

enum MessageResponse{
    SUCCESS,
    FAILURE
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ECSUTILS_H
