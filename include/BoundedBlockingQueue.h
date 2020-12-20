//
// Created by wlx on 2020/12/20.
//

#ifndef CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H
#define CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

class BoundedBlockingQueue {

public:
    explicit BoundedBlockingQueue(int capacity);

    virtual ~BoundedBlockingQueue();

    void enqueue(int element);
    int dequeue();
    int size();

private:
    std::queue<int> q_;
    int cap_{};
    std::mutex m_;
    std::condition_variable cv_;
};


#endif //CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H
