//
// Created by kevin on 8/19/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H

#include <functional>
#include "utils/SensorData.h"


/**
 * Helper macros to abstract the repetitive parts of required lambdas
 * for constructors, see below
 */

/**
 * Macro to construct a void(SensorData&) lambda function
 */
#define CALIBRATION_FUNCT(LINE) std::function<void(SensorData&)>{[](SensorData &data) -> void {\
                                    LINE\
                                }}

/**
 * Macro to construct a int&(SensorData&) lambda function
 */
#define INT_SELECTOR_FUNCT(FIELD) std::function<int&(SensorData&)>{[](SensorData& data) -> int& { \
                                    return data.FIELD;   \
                                 }}

/**
 * Class that applies a calibration to a given SensorData object
 *
 * We model calibrations as an object that mutates a SensorData,
 * usually by just changing one of its field according to a given
 * formula
 *
 * TDLR: It's basically just an encapsulated lambda function
 */
class SensorDataCalibrator {
public:
    /**
     * This is the most general and powerful constructor for the object
     *
     * As noted above, a calibrator is basically a lambda function that mutates a
     * SensorData
     *
     * This constructor gives the ability to specify what exactly that function is,
     * with no restrictions. Use wisely
     *
     * @param fieldMutator lambda function to store
     */
    explicit SensorDataCalibrator(std::function<void(SensorData&)> fieldMutator);

    /**
     * A more specialized construction, for individual fields on a SensorData
     *
     * In general, our calibrations flow something like
     * - get data from SENSOR1
     * - apply a mathematical formula to data
     * - store applied data back into SENSOR1
     *
     * While this is certainly possible to do with the most powerful constructor,
     * this constructor makes it much less error prone and repetitive with our macros
     *
     * @param selector a lambda function that returns which field, of type T in a SensorData
     * to calibrate
     * @param calibrationFormula the mathematical formula to apply on the field,
     * has type const T& -> T
     */
    template<typename T>
    SensorDataCalibrator(T SensorData::* field,
                         std::function<T(const T&)> calibrationFormula):
    SensorDataCalibrator([field, calibrationFormula](SensorData& data){
        T selectedData = data.*field;
        data.*field = calibrationFormula(selectedData);
    }){}

    /**
     * Application function, this will very likely mutate the passed in data
     * @param data data to be tweaked
     */
    void applyCalibration(SensorData& data);
private:
    std::function<void(SensorData&)> fieldMutator;
};


/**
 * These are convenience functions for describing a function on a int
 */
namespace IntFuncts {
    /**
     * Produces a function from int to int that applies the formula
     * a(x^2) + b(x) + c to any x
     *
     * @param a
     * @param b
     * @param c
     * @return a std::function<int(int)>
     */
    std::function<int(const int&)> Quadratic(double a, double b, double c);

    /**
     * Produces a function from int to int that applies the formula
     * m(x) + b to any x
     *
     * @param m
     * @param b
     * @return a std::function<int(int)>
     */
    std::function<int(const int&)> Linear(double m, double b);
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATACALIBRATOR_H
