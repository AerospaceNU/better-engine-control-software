//
// Created by kevin on 7/26/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
//TODO: actually use calibrators in our boundary
class IntCalibrator{
public:
    /**
     * Gets calibrated value
     * @param rawValue
     * @return calibrated value
     */
    virtual int applyCalibration(int rawValue) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IntCalibrator() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_INTCALIBRATOR_H
