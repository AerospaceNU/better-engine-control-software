/**
* This file is the main file for building a complete ecs on the Raspberry Pi
*/

#include "ecs/HorizontalECS.h"
#include "comm-boundary/ECSNetworker.h"
#include "phys-boundary/TeensyBoundary.h"
#include "sequencer/Sequencer.h"
#include "watchdog/WatchDog.h"

//class A{
//public:
//    A(B& );
//private:
//    B& ref;
//};
//
//class B{
//public:
//    B(A& );
//private:
//    A& ref;
//};


int main(){
    //HorizontalECS ecs;

    A foo;
    B bar(foo);
    foo(bar);
    return 0;
}