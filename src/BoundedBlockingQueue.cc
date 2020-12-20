//
// Created by wlx on 2020/12/20.
//

#include "../include/BoundedBlockingQueue.h"


BoundedBlockingQueue::BoundedBlockingQueue(int capacity)
        : cap_(capacity) {

}

BoundedBlockingQueue::~BoundedBlockingQueue() = default;

void BoundedBlockingQueue::enqueue(int element) {
    std::unique_lock<std::mutex> l(m_);
    while (q_.size() >= cap_) cv_.wait(l);
    q_.push(element);
    cv_.notify_all();

}

int BoundedBlockingQueue::dequeue() {
    std::unique_lock<std::mutex> l(m_);
    while (q_.empty()) cv_.wait(l);
    int res = q_.front();
    q_.pop();
    cv_.notify_all();
    return res;
}

int BoundedBlockingQueue::size() {
    return q_.size();
}
