//
// Created by kevin on 8/12/2022.
//

#include "../catch.hpp"
#include "utils-and-constants/ThreadQueue.h"
#include <thread>

TEST_CASE("Thread-safe queue pushing", "[bruh]"){
    ThreadQueue<int> queue;

    auto pushOneLambda = [&queue](){
        queue.push(1);
    };

    std::thread th1(pushOneLambda);
    std::thread th2(pushOneLambda);
    std::thread th3(pushOneLambda);

    th1.join();
    th2.join();
    th3.join();

    REQUIRE(queue.size() == 3);

    REQUIRE(1 == queue.front());
    queue.pop();
    REQUIRE(1 == queue.front());
    queue.pop();
    REQUIRE(1 == queue.front());
    queue.pop();
}

TEST_CASE("Thread-safe queue popping", "[bruh]"){
    ThreadQueue<int> queue;

    queue.push(1);
    queue.push(1);
    queue.push(1);
    REQUIRE(queue.size() == 3);

    auto popOneLambda = [&queue](){
        queue.pop();
    };

    std::thread th1(popOneLambda);
    std::thread th2(popOneLambda);
    std::thread th3(popOneLambda);

    th1.join();
    th2.join();
    th3.join();

    REQUIRE(queue.size() == 0);
}

TEST_CASE("Thread-safe queue popping and pushing at the same time", "[bruh]"){
    ThreadQueue<int> queue;

    // we start with one element, that way if the pop goes first it doesn't throw an exception
    queue.push(1);
    REQUIRE(queue.size() == 1);

    auto popOneLambda = [&queue](){
        queue.pop();
    };

    auto pushOneLambda = [&queue](){
        queue.push(1);
    };

    std::thread th1(pushOneLambda);
    std::thread th2(popOneLambda);
    std::thread th3(pushOneLambda);

    th1.join();
    th2.join();
    th3.join();

    REQUIRE(queue.size() == 2);
}

