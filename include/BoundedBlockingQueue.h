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
    explicit BoundedBlockingQueue(size_t max_size);
    BoundedBlockingQueue(const BoundedBlockingQueue&) = delete;
    BoundedBlockingQueue& operator = (const BoundedBlockingQueue&) = delete;

    virtual ~BoundedBlockingQueue();

    void enqueue(const T& element);
    void dequeue(T& element);
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    bool full() const;

private:
    std::queue<T> q_;
    size_t cap_{};
    mutable std::mutex m_;
    std::condition_variable cv_not_full_;
    std::condition_variable cv_not_empty_;
};


#endif //CPLUSPLUS_CONCURRENT_BOUNDEDBLOCKINGQUEUE_H
