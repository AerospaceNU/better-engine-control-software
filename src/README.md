# ECS Redesign

## What we want this software to do
At the most basic level, our engine control software has to
- ***read sensors***
- ***actuate effectors (the term we call things like valves)***

To actually report results and receive commands, we need
- ***some way to communicate with this software from an operator side***
    - ***it should be able to send and receive, so both ways***

This is the basic functionality that is incorporated into the old
ECS very well. However, over time we wanted additional features.

Rocket engines are dangerous, so we have to monitor the sensor data
to make sure no abnormalities are happening. We would like this to be automatic.
- ***some way to automatically process and check sensor data so that it fits into expected bounds***
- ***this should automatically fire warnings and/or aborts if it detected anything wrong***

Operating the test stand manually can be quite repetitive. Some actions have to be done over
and over, which is rather taxing for a human operator. In addition, some actions have to take
place in a specific timeframe (for example, transitioning to State1 500 milliseconds after State2),
which is rather hard for a human to do. Because of this, we want 
- ***some way to automatically run sequences of actions***
  - ***these sequences should be precise enough to describe split second gaps***

Finally, it is expected that things will go wrong at some point. If this happens, we want to know
what happened, so we can fix it afterwards. So we want
- ***some way to log events***
  - ***it should be saved in some way that we can access it even if the software stops running***

As time went on, we figured that redesigning the current system was necessary to incorporate these features
decently.

## Additional goals
It's not a redesign unless we got extra ideals thrown in :)

Everything we create should be **testable**. We want to be able to make any change, run tests, and be totally confident
that everything continues to work as expected. This will mean that we will need a variety of tests, ranging from
unit-testing with mocks to larger integration tests using several fully fledged objects. Remember, in the end this
software is going to be controlling a dangerous liquid rocket engine. 

## General architecture
We've broken up these requirements into basic objects as follows:

An `IPhysicalBoundary` is responsible reading and writing to sensors and effectors.

A `ICommBoundary` is responsible for communications for the operator both ways

`WatchDog` is responsible for monitoring and alerting abnormal sensor readings
    - it uses another data type, an `IRedline`, that represents a condition that we expect the sensors to be in

`Sequencer` is responsible for automatically running time-gated sequences of events
    - it uses another data type, an `ISequence`, that represents a time-gated sequence of events

Logging is still a bit of a TODO, but currently we are planning on having a Logger object as well

And finally, these objects need synchronization. There has to be something to hand `WatchDog` the sensor data
from `IPhysicalBoundary`, there has to be something to tell `Sequencer` that `ICommBoundary` wants it to
run a sequence, etc. This is the job of the `IECS` object.

> Quick note: object names that start with "I" are interfaces, because we plan to swap them out with different implementations


## Horizontal (and probably Vertical) Test Stand details

The implementing class for `IPhysicalBoundary` is `TeensyBoundary`. How our setup works is that while we can
directly access the valves on the Pi, the sensors are read from a separate Arduino and other circuit boards. So the
TeensyBoundary has to receive this data in packets from a serial port.

The implementing class for `ICommBoundary` is `ECSNetworker`. This class uses Websockets and JSON as external 
dependencies, and sends and receives data through a websocket in a JSON format. We have a GUI on the other end
connected to the same socket that the operator can interact with. 

The implementing class for `IECS` is `HorizontalECS`. This class just does the general work of synchronizing actions.
However, it is important to note that we run `HorizontalECS` and `ECSNetworker` **IN TWO SEPARATE THREADS**. This means
that their methods have to be threadsafe.

Here is the basic UML diagram (arrows represent "has-a", so A->B would mean "A has a B")
![](Test%20Stand%20Basic%20UML.png)

Note how we only have one circular reference, between the `ECSNetworker` and `HorizontalECS`. The rest don't
have any knowledge about the parent IECS object, which is good for easier unit-testing.


## Future plans

First of all, a lot of stuff is still not implemented. So that takes priority

The major change we know we have to make is making an implementation for the custom prop board. This change gives
us things like onboard sensors, so we don't have to do the cringe data packets through serial ports things like the
TeensyBoundary. However, the prop board comes with a major limitation. **It only has space for an EXE with a size
of less than 500KB.** We can do things like compiling a release build, but if that's the only way to get our software
to fit we will be severely hampered when things INEVITABLY go wrong and we can't properly debug. 

This means that the limiting factor we will probably face will be space constraints. Thankfully, a HUGE chunk of our 
current test stand EXE space is used on the `ECSNetworker` with its giant dependencies. When we reimplement it for the 
prop board, the space saved should be DRAMATIC. 

That being said, **DO NOT PREMATURELY OPTIMIZE CODE FOR SPACE** because
- our major space-saving has yet to be finished yet (said comm boundary)
- we have to do some compiler things to remove unnecessary libraries bloating the size
- compiler optimizations can be pretty magical, but they only work if your intentions in code are clear
- if we cannot read/understand over-optimized code, when the inevitable time to debug it come, it is effectively useless
  - we will have to rewrite/replace it
- optimization requires data, we have to know what parts of the code are the chunkiest AFTER we get everything ready
  - do NOT just trust intuition, computers are complex and compilers are magical

If we come to a point where we need to optimize, we can analyse the data and decide as a group.