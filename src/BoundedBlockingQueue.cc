//
// Created by wlx on 2020/12/20.
//

#include "../include/BoundedBlockingQueue.h"

template<typename T>
BoundedBlockingQueue<T>::BoundedBlockingQueue(int capacity)
        : cap_(capacity) {

}

template<typename T>
BoundedBlockingQueue<T>::~BoundedBlockingQueue() = default;

template<typename T>
void BoundedBlockingQueue<T>::enqueue(const T& element) {
    std::unique_lock<std::mutex> l(m_);
    while (q_.size() >= cap_){
        cv_.wait(l);
    }
    q_.push(element);
    cv_.notify_one();
}

template<typename T>
void BoundedBlockingQueue<T>::dequeue(T& element) {
    std::unique_lock<std::mutex> l(m_);
    while (q_.empty()){
        cv_.wait(l);
    }
    element = q_.front();
    q_.pop();
}

template<typename T>
int BoundedBlockingQueue<T>::size() {
    std::unique_lock<std::mutex> l(m_);
    return q_.size();
}

template<typename T>
bool BoundedBlockingQueue<T>::empty() {
    std::unique_lock<std::mutex> l(m_);
    return q_.empty();
}
