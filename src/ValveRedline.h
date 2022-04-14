//
// Created by allison on 4/13/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H

class ValveRedline: public Redline{
public:
    ValveRedline(std::string n, std::function<ECSValveState(SensorData*)> sFunct, ECSValveState state);
    bool testCondition(SensorData* data);

protected:
    std::function<ECSValveState(SensorData*)> selector;
    ECSValveState state;
    bool checkWithin(int);
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_VALVEREDLINE_H
