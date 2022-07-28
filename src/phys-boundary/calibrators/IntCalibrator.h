//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
class IntCalibrator{
public:
    virtual int applyCalibration(int rawValue) = 0;
    virtual ~IntCalibrator() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
