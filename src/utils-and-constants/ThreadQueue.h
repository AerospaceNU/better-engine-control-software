//
// Created by kevin on 7/11/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_THREADQUEUE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_THREADQUEUE_H

#include <mutex>
#include <queue>
#include <stdexcept>

/**
 * An implementation of a generic LIFO queue that is safe even when multithreaded.
 *
 * @tparam T generic type of item in queue
 */
 //TODO: make custom exceptions lmao
template <typename T>
class ThreadQueue {
public:
    explicit ThreadQueue(const std::queue<T>& q):
        queue(q)
    {}

    /**
     * Adds item to back of queue
     * @param item item to add
     */
    //im PRETTY sure queue will actually make a copy of the item
    //internally
    void push(const T& item){
        std::lock_guard<std::mutex> lock(queueMutex);

        queue.push(item);
    }

    /**
     * Returns the current amount of items in the queue.
     *
     * NOTE: this method should used with caution. Between methods calls, other threads can modify
     * the queue. So after calling size(), another thread can pop or push to modify the item count
     *
     * Example:
     * queue.size();
     * [ANYTHING CAN HAPPEN IN BETWEEN HERE FROM OTHER THREADS]
     * queue.pop()
     *
     * If using it as a check before pop()/front(), size() will only be reliable if only one thread is popping
     * from the queue (single-consumer)
     *
     * If you are not using this queue in a single-consumer, you will have to rely on the exceptions
     * thrown from front() and pop() when the queue is empty
     *
     * @return num of items currently in queue
     */
    unsigned int size(){
        std::lock_guard<std::mutex> lock(queueMutex);

        return queue.size();
    }

    /**
     * Returns the first item in the queue
     *
     * @return first item
     * @throws TODO (currently std::runtime_error) if queue is empty
     */
    T& front(){
        std::lock_guard<std::mutex> lock(queueMutex);

        if (queue.empty()){
            throw std::runtime_error("Tried to get front of empty queue!");
        }

        return queue.front();
    }

    /**
     * Removes the first element from the queue
     *
     * @throws TODO (currently std::runtime_error) if queue is empty
     */
    void pop(){
        std::lock_guard<std::mutex> lock(queueMutex);

        if (queue.empty()){
            throw std::runtime_error("Tried to pop from an empty queue!");
        }

        queue.pop();
    }

private:
    std::queue<T> queue;
    std::mutex queueMutex;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_THREADQUEUE_H
