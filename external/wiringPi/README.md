It would be awesome if we didn't have to do this dumb build from .so files for this library, but a few things stand
in our way.

The wiringPi project doesn't actually use CMake as their build system, they use raw Make files. To integrate these
into our CMake is actually a lot of work.

There have been a few forks of the wiringPi codebase that change the build system to CMake, namely 
[this one](https://github.com/WiringPi/WiringPi/pull/110) and [this one](https://github.com/WiringPi/WiringPi/pull/48).
But each of these have a few problems. 

First, we should point out that this wiringPi codebase is unofficial. The og maintainer of wiringPi, gave up quite a 
while back, so this GitHub is really just a fork. The last official update was 
[this one](https://github.com/WiringPi/WiringPi/tree/final_official_2.50). The important thing is that this was in
late 2019.

Until now, we've been using the system wiringPi installed on our RPi. I don't know what version of the wiringPi code this
is. This is a problem for our second CMake option, because it was made in goddamn 2016, aka old as fuck. It might not
have new code changes incorporated, and if our code depends on these "new" features we're kinda boned.

As for the first CMake option, apparently the CMakes are kinda shit from what I can tell from the conversation. Probably
best to avoid.

So there go our current options. It would be amazing if there was another CMake fork I haven't found that actually
satisfies our needs. But that's kind of wistful thinking. What we COULD realistically do is make our own fork, and
add the CMakeFiles ourselves. If we could get it merged into the main repo, then we could leech off future improvements 
as well. However, this is a pretty big TODO
