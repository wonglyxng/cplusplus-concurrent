//
// Created by wlx on 2020/12/20.
//

#ifndef CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H
#define CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BoundedBlockingQueue {

public:
    explicit BoundedBlockingQueue(int capacity);

    virtual ~BoundedBlockingQueue();

    void enqueue(const T& element);
    void dequeue(T& element);
    int size();
    bool empty();

private:
    std::queue<T> q_;
    int cap_{};
    mutable std::mutex m_;
    std::condition_variable cv_;
};


#endif //CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H
