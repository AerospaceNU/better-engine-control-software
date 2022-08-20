//
// Created by kevin on 8/12/2022.
//

#include "../catch.hpp"
#include "utils/ThreadQueue.h"
#include <thread>


TEST_CASE("ThreadQueue multithreaded tests", "[unit]"){
    ThreadQueue<int> queue;

    auto pushOneLambda = [&queue](){
        queue.push(1);
    };

    auto popOneLambda = [&queue](){
        queue.pop();
    };

    SECTION("Concurrent queue pushing") {
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

    SECTION("Concurrent queue popping") {
        queue.push(1);
        queue.push(1);
        queue.push(1);
        REQUIRE(queue.size() == 3);

        std::thread th1(popOneLambda);
        std::thread th2(popOneLambda);
        std::thread th3(popOneLambda);

        th1.join();
        th2.join();
        th3.join();

        REQUIRE(queue.size() == 0);
    }

    SECTION("Concurrent queue pushing AND popping") {
        // we start with one element, that way if the pop goes first it doesn't throw an exception
        queue.push(1);
        REQUIRE(queue.size() == 1);

        std::thread th1(pushOneLambda);
        std::thread th2(popOneLambda);
        std::thread th3(pushOneLambda);

        th1.join();
        th2.join();
        th3.join();

        REQUIRE(queue.size() == 2);
    }
}
