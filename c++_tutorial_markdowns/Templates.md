# Templates

Templates are the most deep, powerful, fucked up, and controversial part of C++. The worst compiler error message you'll ever see? Because of templates. The most elegant, "how tf does that work at compile time" feature in C++? Because of templates.

```text
For the nerds out there, the template system is actually Turing-complete! Which is cool and terrifying!
```


In this tutorial, we are going to cover templates at their most basic use case, generics. Because gonna be real, I don't know anything more than that either.

## Problem
Let's say that we want to represent a data type, that contains two of something, we'll call it a pair. Say in this case, we want an `int` and a `float`

We quickly model it with a basic struct
```c++
struct PairIntAndFloat{
    int first;
    float second;
};
```
usage looks like:
```c++
PairIntAndFloat pair;
```

It's a hit feature, everyone loves your work and your struct is widely used. But later, someone asks you to apply your genius to making another pair, with a `char` and a `double` this time. You oblige, and your hard work brings you to
```c++
struct PairCharAndDouble{
    char first;
    double second;
};
```
with usage like:
```c++
PairCharAndDouble pair;
```

Once again to loud applause and glory, claiming you to be the authority on pairs. Very soon you get another request, asking you to make a pair for `std::string` and `unsigned int`. After much effort, you arrive at
```c++
#include <string>
struct PairStdStringAndUnsignedInt{
    std::string first;
    unsigned int second;
};
```

At this point you are happy to be praised, but you also want to move onto different things. However, the demand for the pair expert is growing, and each of the demands involves different types, requiring different pair definitions each time, taking up your valuable time.

## Solution
It should hopefully be very obvious that there is barely anything changing in these pair definitions.

```c++
struct PairIntAndFloat{
    int first;
    float second;
};

struct PairCharAndDouble{
    char first;
    double second;
};

#include <string>
struct PairStdStringAndUnsignedInt{
    std::string first;
    unsigned int second;
};
```

The only thing that is changing is the types of the `first` and `second` fields.  It's unironically a copy-paste job, and whenever you feel that your senses for potential abstraction should be triggered. 

If only we could parametrize these types, let the user specify what types `first` and `second` should be, and have the compiler "copy paste them" into a new pair struct definition, we wouldn't need to manually do this.

Enter templates, with C++ the solution looks like this
```c++
template <typename TypeOfFirst, typename TypeOfSecond>
struct Pair{
    TypeOfFirst first;
    TypeOfSecond second;
};
```

Hopefully the similarities with the before structs should be obvious. We parameterize the types, that's what the `TypeOfFirst` and `TypeOfSecond` represent. The two of them are our *template parameters/arguments* and we use them as the type of the `first` and `second` fields.

In an actual codebase, we would probably name the typenames differently, like
```c++
template <typename A, typename B>
struct Pair{
    A first;
    B second;
};
```

> If you're curious about how a type is "represented" in C++, like what size it is, etc, there's nothing. Types are only a thing that exist at compile time. Once the final binary executable is popped out, there are no representations of types anywhere.

Now we can use this struct easily as well, we just have to tell it what two types to use, like so
```c++
Pair<int, float> pair1;
Pair<char, double> pair2;
Pair<std::string, unsigned int> pair3;
```

For `pair1`, which we want to be a `int` and `float` pair like `PairIntAndFloat`, we call the template class `Pair` and set its `TypeOfFirst` to be `int` and `TypeOfSecond` to be `float`. through the *template parameters* that we set in brackets;

And yeah, that's templates 101, it's how we get generic programming in C++

## A few more things

I mentioned before that templates are the deepest part of C++. I'll try to push that a bit and get your brain thinking.

First of all, the example I showed above had types as the template arguments. But actually, you can have regular ass data types as template parameters

```c++
template <int N>
struct NumberReturner{
    int returnNum(){
        return N;
    }
};
```
[Give it a run, it works!](https://godbolt.org/z/3x9TeG9GY)

Why you might ask? Well, templates do all their work at compile time. A regular `NumberReturner` that say, had a constructor and a field to store the `int` technically takes more time and space at runtime, at the upside of being much more flexible. 

And sometimes you just need a value at compile time, for example C-style array lengths, and you can only provide that with template parameters (take a look at `std::array`, the modern C++ equivalent of C-style arrays. can you guess how it's implemented?)

Finally, I'll just spit out some buzzwords. Templates are lazy-instantiated. They allow SFINAE (Substitution Failure Is Not An Error). Search them up if you're interested, this is where the real fun begins.