# TODO

## How C++ is compiled
TODO: headers and preprocessor, object files, linker

General gist: https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work

## Declarations and definitions (ODR)
TODO

## Namespaces
TODO

## Pointers vs references
Differences between the two: https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable

TODO

## Passing by reference vs. value
TODO

## Overloading functions
TODO

## Memory management/heap allocation (and safety)
TODO

## Undefined behavior (vs unspecified behavior and implementation specific behavior)
Undefined behavior is probably the hardest part of coding in C++ and C. It's worth getting out of the way right now that undefined behavior (we call it UB) might have a different connotation to you, coming from other languages. UB in other languages is usually more similiar to implementation specific behavior in C++, a more technical explanation can be found [here](https://stackoverflow.com/a/4105123/12310828)

When you invoke UB, you can assume nothing at all about your program. Period. [It's a bit of a running joke to say that the compiler is allowed to make demons fly out your nose in the case of UB](http://www.catb.org/jargon/html/N/nasal-demons.html). If it happens to work/give a result you can use, it probably won't on a different OS. It probably won't on a different compiler. It probably won't on the same compiler, but different version. It probably won't on the same compiler on the same version, with a few extra optimizations on.


There are (unironically) hundreds of cases of UB. One you might see is read from initialized variables.
```c++
int x; //oops, i forgot to initialize it

std::cout << x; // let's print it!
```

What does this program produce? If you run it, you might see some barf of random numbers. You might see nothing printed. Those are quite likely. You might see `"Hello world"` printed. You might see your program crash. You might see your computer crash. You might see your computer open Internet Explorer. Once again, UB means no guarantees at all.

Hopefully this is at least a bit scary to you. But the killer punchline of UB is that ***the compiler is allowed to assume UB never happens***. Why is this so dangerous? Because modern optimizing compilers can in essence reason about your code. And with the ability to assume that UB doesn't happen, this can absolutely nuke the control flow of your compiled code if you aren't careful.

Take for example, this code
```c++
#include <iostream>

void testFunction(int* pointer){
    // we dereference the pointer blindly
    int x = *pointer;

    // now, we check if it's NULL
    // but wait, we already dereferenced it.
    // dereferencing a NULL pointer would be UB
    // the compiler is allowed to assume UB
    // doesn't happen. So logically, speaking...
    if (pointer == NULL){
        std::cout << "Uh oh!";
    }

    std::cout << x;
}
```
Where we probably mess up by swapping the if statement after the deference. Now the compiler is allowed to deduce that `pointer` is never NULL due to dereferencing it, so the if statement should never trigger.

[Don't believe me?](https://gcc.godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbKQADqgKhE4MHt6%2BekkpjgJBIeEsUTHxdpgOaUIETMQEGT5%2BXLaY9nkM1bUEBWGR0XG2NXUNWc0KQ93BvcX9sQCUtqhexMjsHOYAzMHI3lgA1CYbbk7jxJish9gmGgCC1zcAbqh46HsEmOMAYl4MlQIQwQIACo9klAdE5iYAOxWW57eF7AD0iL2AHdMHssGcqNFGKs3ggMWDBNE9hFaMF0LQAJ73BF7QF7VQHDYAET2QOJ72Ih1hdzhCORewYqFRpDRGOQhOQAGsGVQGQQwBwFMKvLRaHTBSiIl4CGimIRxei9mIzkx0NTMbicWdfphXoQAHRa%2BFCrGYW144LAU17UJyAIBUHPEnEBmquR8%2BlCgiEvZoFgJOikvCqsS0UUOt6oU0KBQ%2BDFR11IlHoVAfBjK/UIJgJBKMJ17IS5zPAPCiDXU8UKBtMGU%2Bp1Dkt4BUQLmkw6sqf%2BwMBSEwkv08boEAoJb6w5uLcHMxmOQIPaoBBgMDmMy8kvQ6e3EsrtdoPUs7dHJmX29Qm83DgLWicACsvB%2BBwWikKgnDbpY1h7AoSwrBimw8KQBCaD%2BCwyiAGwbE6WG4Xh%2BH6JwkhAahYGcLwCggBoyGoQscCwEgibJvQZAUBATEpjEwBcBszRYA8HaYAAangmCogA8g2wFITQtDcpREARKRETBLU1KcEhKnMMQ1LiRE2gVCh3C8ImbCCOJDA0qRWAsIYwDiCBvD4GclQPB8pGYKoFR6msSHgn%2Bxn6HgETEGpHhYKRBDEHgLAaT%2BfAGMACgiWJkmMHFMiCCIYjsFImXyEoaikbozQGEYKDWNYQURJRkALKgCTtJRHAALTiRoewtS1K5TqYUGWGYoHlH8fgQK4IxNKQgRTEUJTZMkqQCBN825GkPSzf0YytIZVQTMtW1tLtXTrX0MRjHtniNHo4zHTNp0SAssHLKsD2ERwgGkMBoHgRwTIAByxC1sSSHswDIMgew8U6XB7BAuCECQu68XMvBGVoczoZh2H4TjuFvcRn2kT9FFUTRjl0TAiDrkmnHkJQHEsSA3G8aQ/GCSlElSRlsnyZQSmOaQWlqRlQs6XpBkOBlpmMAQFlWQLNl2Q5oHOTtbnNaBnnee8GX%2BaRFIhWFGBrKBUUxXFCxUIlyWiZz6WBfwWWdrl0iOwVKjqALuhmPodkVf1NgG7VED1Y1aTNW1MNdT1bJ9VYA1DdtI0uAw7iXaMU2pydMxnYkC3tPteerfkd059dSftJ0wzp5Nw2VxM2dzedXSFzddSN5tj1wS9XC/gBJECz9/2A8DoPg5D2Ew3D%2BBEOGiEo2T6OY1hOG4zj%2BMD995G2KTaNoW9Zib7wxOL/vbnECkziSEAA%3D%3D%3D) At just one level of optimization, the second `call    std::basic_ostream` is completely removed because the compiler deduces that the if statement must always be false. THAT is why UB is fucked up. It makes an error in your program from "Oh haha whoops I segfaulted from dereferencing the null pointer" into "My program literally does not contain the ability to even print in the if statement because my compiler deduced that it was impossible from one silly mistake and now my compiled code is completely unexpected from what I thought I programmed"

Don't think that is this a bug that would happen in real life? [Ask the authors of the mfing Linux kernel (written in C) about a very interesting incident...](https://lwn.net/Articles/342330/)

Finally, listing off some common UB cases that you should be aware of
- dereferencing a null pointer
- reading uninitialized data
- reading freed memory
- division by 0
- signed integer overflow (NOTE: unsigned integer overflow is well defined!)
- pointer arithmetic to out of bounds pointers
- [strict aliasing](https://stackoverflow.com/q/98650/12310828)
- statements like `i++ + ++i;`
- data races in multithreaded environments

and more can be found [here](https://stackoverflow.com/q/367633/12310828)
