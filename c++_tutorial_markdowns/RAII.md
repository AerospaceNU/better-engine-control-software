# RAII explanation

## Problem Description

In programming, we typically have to deal with things we have to *take* and *give back*. We call these things *resources*, and we will model one as

```c++
struct Resource {
    void acquire() {
        std::cout << "Resource acquired!" << std::endl;
    }

    void release() {
        std::cout << "Resource released!" << std::endl;
    }
};
```
> Don't forget to #include \<iostream>

You would use it something like

```c++
int main(){
    Resource r;
    r.acquire();
    r.release();
}
```

and you should see something like this in the console

```text
Resource acquired!
Resource released!
```

We always always always need to see a `Resource released!` text for every `Resource acquired!` text. This represents us releasing the resource after we finish using it.

There are a few ways we would go about using this resource. The naive way would be to just code like we have before, a typical use of this resource would be something like

```c++
int function1(){
    Resource r;
    r.acquire();
    doSomething();
    /**
    maybe hundreds of lines of more code...
    */
    r.release();
}
```

This approach has two problems, in order of severity

1. It is hard to ensure that we actually call `release()`. If the `release()` call is far enough away from the `acquire()` call, the writer might forget to write it. And in code review, the reader might forget about the `release()` call for the same reason, so this approach is prone to human error (just think about if we were juggling 5+ resources!).

2. This code is exception-unsafe. What if `doSomething()` was implemented like

```c++
#include <stdexcept>

void doSomething() {
    throw std::invalid_argument{"doyyyyyyyyy"};
}
```

so that our total code looks something like

```c++
#include <iostream>
#include <stdexcept>

struct Resource {
    void acquire() {
        std::cout << "Resource acquired!" << std::endl;
    }

    void release() {
        std::cout << "Resource released!" << std::endl;
    }
};

void doSomething() {
    throw std::invalid_argument{"doyyyyyyyyy"};
}

void function1(){
    Resource r;
    r.acquire();
    doSomething();
    /**
    maybe hundreds of lines of more code...
    */
    r.release();
}

int main() {
    try{
        function1();
    }
    catch(...){

    }
}
```

> The main method is just catching all the exceptions, so you don't get a weird termination error popup.

Run this code and you should see that we only have
```text
Resource acquired!
```

in the console. In other words, our resource wasn't released, the `release()` call wasn't run.

Why is that? We can clearly see the `release()` call. Well, mentally tracing through `function1()`, we `acquire()` the resource, then call `doSomething()`. Except it throws an exception that leaves `doSomething()`. When the exception reaches the calling function `function1()`, it sees no catch block, so it traces up to `main()` where it is finally caught. However, notice how we never got to anything past `doSomething()` in the `function1()` call because of the exception. So `release()` was never called, and the resource is leaked.

This is a problem that plagues **every single language** with exceptions, not just C++. We call it exception safety.

Taking a step back, what could be a way to solve this problem? One solution is if we had some way to tell our coding language, `"hey, these lines of code? I want them to be run EVEN IF an exception is thrown, EVEN IF the control flow doesn't directly reach them."` In the worst case, you get something like Java's `try-catch-finally` construct, where the `finally` provides this unconditional running. However, C++ has a much more elegant solution to this.

## A detour

An class has at least one *constructor*, which you are probably familiar with implementing, and a single *destructor*, which is responsible for destroying the object after we are done with. You might not have ever seen a destructor method, let alone implemented one, because C++ will generate a default destructor for you on every object. But we will explore it here.

Even though constructors have the duty of making the object, and destructors have the duty of destroying an object, in the body of the methods you can put anything you want in it, just like a regular function. So let's make this class

```c++
struct CustomConstructorAndDestructor {
    //constructor taking in no params (the default constructor)
    CustomConstructorAndDestructor(){
        std::cout << "Made an object!" << std::endl;
    }
    
    //the destructor
    ~CustomConstructorAndDestructor(){
        std::cout << "Destroyed an object!" << std::endl;
    }
};
```

and then setup functions like
```c++
void function2(){
    CustomConstructorAndDestructor obj{};
}

int main() {
    try{
        function2();
    }
    catch(...){

    }
}
```
and run it. `main()` calls `function2()`, which makes a `CustomConstructorAndDestructor` object named `obj` as a local variable. You should see 
```text
Made an object!
Destroyed an object!
```
in the console.

You might be a bit confused on where the destructor is called. After all, there's nothing resembling `~CustomConstructorAndDestructor()` anywhere in `function2()`. The destructor is called when the `obj` goes out of scope here, at the end of the function. Annotating it a bit, `function2()` works like

```c++
void function2(){
    CustomConstructorAndDestructor obj{}; // construct with default constructor
} // end of function, obj out of scope, obj's destructor is called
```

It's important to note, the destructor is called when `obj` is out of scope, which is **not necessarily at the end of the function**. For example, try putting `CustomConstructorAndDestructor obj{}` in the body of a loop.

Let's modify `function2()`, so that we throw an exception after `obj` is constructed

```c++
void function2(){
    CustomConstructorAndDestructor obj{};
    throw std::invalid_argument{"doyyyyyyyyy"};
} 
```

Run your code and notice the console text
```text
Made an object!
Destroyed an object!
```
is exactly the same.

Why? Indeed, from what we described above the mechanism for calling `obj`'s destructor isn't very clear in this case. After all, the function never reached the end of the function, where we said `obj`'s end of scope was. 

The key is that C++ makes a CRUCIAL guarantee, copied from Wikipedia:

> C++ guarantees that all stack objects are destroyed at the end of the enclosing scope, known as stack unwinding. The destructors of both the lock and file objects are therefore guaranteed to be called when returning from the function, whether an exception has been thrown or not

In other words, if you have a local variable (like `obj`), it's destructor will be called whether or not the function exits normally, or from an exception.

> This is even more reason to avoid the use of `new` to create objects, because you lose this guarantee!

In other words, this is our unconditional code execution we've been looking for.

## RAII full power

RAII stands for *"Resource acquisition is initialization"*. This is agreed upon to be a pretty dogshit name. The real power in RAII comes from unconditional destructor execution, not initialization/construction. Alternative names include *"Constructor Acquires, Destructor Releases"*(CADRe) and *"Scope-based Resource Management"* (SBRM) if they provide more clarity to you, but we're kinda stuck with RAII as the name because of the community.

> You can delete the `CustomConstructorAndDestructor` and `function2()` now.

We will create `ResourceHandler` to manage `Resource`s. Based on the `Problem` section, we need unconditional code execution, which only happens in destructor methods. We want to run `release()` unconditionally, sp this forces us to make a new class that will call it in its destructor. We call classes like these RAII objects/handlers.

We start with 

```c++
class ResourceHandler{
public:
    ~ResourceHandler(){
        resourceToHandle.release();
    };

private:
    Resource& resourceToHandle;
};
```

This takes care of our destructor/release part. Now, we make our constructor. It needs to take in a reference to a Resource object so the object knows which object to call `acquire()` and `release()` on. In addition, thanks to the name *"Resource acquisition is initialization"*, we should call `acquire()` inside the constructor.

So our class looks like
```c++
class ResourceHandler{
public:
    explicit ResourceHandler(Resource& resourceToHandle_):
        resourceToHandle(resourceToHandle_)
    {
        this->resourceToHandle.acquire();
    }
    
    ~ResourceHandler(){
        this->resourceToHandle.release();
    };

private:
    Resource& resourceToHandle;
};
```

> IMPORTANT FUCKING NOTE: We have manually defined a destructor for `ResourceHandler`. Our code will compile, but you need to obey the Rule of Three/Five, aka implement copy/move constructors and copy/move assignment operators for `ResourceHandler` as well if you don't want to be blown up. This is important for actual use, but outside the scope of this tutorial so we will jump to the final result of

```c++
class ResourceHandler{
public:
    explicit ResourceHandler(Resource& resourceToHandle_):
        resourceToHandle(resourceToHandle_)
    {
        this->resourceToHandle.acquire();
    }
    
    //copy constructor
    ResourceHandler(const ResourceHandler& other) = delete;
    //move constructor
    ResourceHandler(ResourceHandler&& other) noexcept = delete;
    //copy and move assignment operator
    ResourceHandler& operator=(ResourceHandler other) = delete;

    ~ResourceHandler(){
        this->resourceToHandle.release();
    };

private:
    Resource& resourceToHandle;
};
```

> If you didn't understand that last step, it's not important to the mechanism of RAII. But it is important to be able to use the class safely, so google `Rule of Three/Five in C++` if this is unfamiliar.

We are ready to see the final result. Setup `function3` and `main` like
```c++
void function3(){
    Resource r;
    ResourceHandler handler{r};
    doSomething();
    /**
    maybe hundreds of lines of more code...
    */
}

int main() {
    try{
        function3();
    }
    catch(...){

    }
}
```

with `doSomething()` still being the function that just throws an exception, and we should still see the beautiful

```text
Resource acquired!
Resource released!
```

If you want, remove the `doSomething` call, so we have

```c++
void function3(){
    Resource r;
    ResourceHandler handler{r};
    /**
    maybe hundreds of lines of more code...
    */
}
```
and we still get the same beautiful result.

## Final catches and final thoughts

TODO: mention anonymous scopes

To properly implement RAII, you need to be wary of

1. Rule of Three/Five as mentioned above

2. Destructors cannot throw exceptions. At all. If they do your whole program will terminate. So your RAII object cannot throw any exceptions during its cleanup. If you want to know why, and maybe some workarounds, google `raii throwing destructors`
