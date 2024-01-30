// Created by Anushka Kulkarni on 10/2/23.
//
#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_GLOBALCOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_GLOBALCOMMBOUNDARY_H

class GlobalCommBoundary {
public:
    /**
     * Sets the global variable for communication, sending data
     */
    virtual void bindCommObject() = 0;

    /**
     * Returns the current value of the communication, reporting data back
     */
    virtual void getCommObject() = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~GlobalCommBoundary() = default;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ICOMMBOUNDARY_H
