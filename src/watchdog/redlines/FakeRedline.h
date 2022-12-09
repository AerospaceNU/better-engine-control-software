//
// Created by kevin on 12/8/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE_H

#include "IRedline.h"

/**
 * An implementation of IRedline that always returns a configured response
 *
 * Useful for unit testing
 */
class FakeRedline: public IRedline{
public:
    FakeRedline(std::string name, ECSRedLineResponse result);

    std::string getName() const override;

    /**
     * Always returns the response passed in constructor
     * @param data ignored
     * @return alwaysResponse field
     */
    ECSRedLineResponse testCondition(SensorData& data) override;

    std::unique_ptr<IRedline> clone() override;

private:
    std::string name;
    ECSRedLineResponse alwaysResponse;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEREDLINE_H
