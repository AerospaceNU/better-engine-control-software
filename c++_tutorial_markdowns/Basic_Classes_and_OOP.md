# OOP

## Structs

At the most basic level, you will find yourself wanting to group multiple pieces of data together. Practically 
every single coding language gives you a way to do this, in C++ you can accomplish this with `struct` s

For example, take the RGB format for color. It is of course perfectly possible to write functions like

```c++
void whatever(int red, int green, int blue){
    //blah blah blah
}
```

However, this will become very repetitive very quickly if you want to make more functions that take in RGB. A more efficient solution is to make a struct,
```c++
struct RGB {
    int red;
    int green;
    int blue;
}
```

Now, each `RGB` struct will have a int for `red`, `green`, and `blue`. We call these *fields*.

one way to set up a `RGB` variable would be something like
```c++
RGB var;
var.red = 100;
var.green = 15 + 1;
var.blue = someFunctionThatReturnsAnInt();
```
> Be careful with initializing in this way! If you forget a field and try to use it later, the compiler won't care, and you hit UB. More ways on how to avoid this later

and now you can pass it in into functions and use it like so
```c++
void whatever(RGB rgb_struct){
    doSomething(rgb_struct.red);
    doSomethingElse(rgb_struct.green);
    doSomethingElse(rgb_struct.blue);
}
```

The `.red`, `.green`, and `.blue` is how you access fields


## Classes and encapsulation

Now with our shiny new `RGB` struct, we implement a lot of functions like
```c++
void whatever1(RGB rgb_struct){
    ... rgb_struct.red
    ... rgb_struct.green ...
    ... rgb_struct.blue ...
}

void whatever2(RGB rgb_struct){
    ... rgb_struct.red
    ... rgb_struct.green ...
    ... rgb_struct.blue ...
}

void whatever3(RGB rgb_struct){
    ... rgb_struct.red
    ... rgb_struct.green ...
    ... rgb_struct.blue ...
}

void whatever4(RGB rgb_struct){
    ... rgb_struct.red
    ... rgb_struct.green ...
    ... rgb_struct.blue ...
}
```
basically accessing fields of `RGB` freely, scattered across tons of functions and different source files.

But what we decided that `RGB` would be better using a `std::vector` instead of 3 separate `int` fields? Well, we can change the `RGB` declaration.

> yes, this example is a bit unrealistic (like really, why tf would you want to change the structure of such a simple struct). but it's simple as a learning lesson

```c++
struct RGB {
    std::vector<int> values;
}
```

But now, all your previously written functions will fail to compile! Why? Because your functions were written calling the `red`, `green`, and `blue` fields, which we just removed! Thankfully, the compiler will actually fail to compile and point out where to patch your functions, but this is still just busy work.

Could we have avoided this? Yes, if we had designed for it beforehand. What if we defined the first `RGB` like this.
```c++
struct RGB {
    int getRed(){
        return this->red;
    }

    int getGreen(){
        return this->green;
    }

    int getBlue(){
        return this->blue;
    }
    int red;
    int green;
    int blue;
}
```

TODO: probably introduce `this` pointer beforehand

and in our functions, instead of calling `.red` and such directly, we called `getRed()` and friends?

Well, then when we switch our struct definition to
```c++
struct RGB {
    int getRed(){
        return this->values[0];
    }

    int getGreen(){
        return this->values[1];
    }

    int getBlue(){
        return this->values[2];
    }

    std::vector<int> values;
}
```

As long as we update the `getRed()` methods correctly, all those functions will still work fine! We still had to change some code due to this struct change, that is fundamentally unavoidable if you think about it. But the difference is that before, we would have to update every single function. Now, we just update 3 functions, and our other functions can just leech off the changes to `getRed()` and such.

But, there's a problem. It's a bit wishful thinking to assume that all users will call with `.getRed()` instead of `.red`. There will surely be some people who miss the memo, use `.red` and their code compiles and works fine, until this change. No unit test is going to catch that. What we need is some way to tell the compiler, "Hey, these things in a struct definition? Don't let other people use them"

And this is exactly `public`/`private`

```c++
struct RGB {
public:
    int getRed(){
        return this->values[0];
    }

    int getGreen(){
        return this->values[1];
    }

    int getBlue(){
        return this->values[2];
    }
private:
    std::vector<int> values;
}
```

Other methods that use `RGB` will not be able to access `private` things in `RGB`. Here, `values` is a private field, but methods can be private as well. `getRGB()` and friends are public.

so functions like

```c++
void whatever(RGB rgb_struct){
    doSomething(rgb_struct.getRed());
}
```

will compile, but
```c++
void whatever(RGB rgb_struct){
    doSomething(rgb_struct.values[0]);
}
```
won't. And this is exactly what we want! We call this term *encapsulation*.

> Encapsulation as we explained it here seems merely useful as a way of giving implementors a bit more freedom to change things. And indeed that is true, but encapsulation will turn out to be CRITICAL later as a way to preserve *invariants*, but story for another day

## Virtual functions/dynamic dispatch

This is where shit really starts to take off. It might be confusing at first how this works, and it will take longer before you realize why this is even useful. The entirety of Fundies 2 for CS is based around hammering this concept into your head, so if this is your first time seeing it, don't be discouraged if this is hard to wrap your head around at first.

## A few quirks of inheritance in C++

TODO: object slicing

TODO: need for dynamic allocation