//
// Created by wlx on 2020/12/20.
//

#include "../include/BoundedBlockingQueue.h"

template<typename T>
BoundedBlockingQueue<T>::BoundedBlockingQueue(size_t capacity)
        : cap_(capacity) {
}

template<typename T>
BoundedBlockingQueue<T>::~BoundedBlockingQueue() = default;

template<typename T>
void BoundedBlockingQueue<T>::enqueue(const T& element) {
    std::unique_lock<std::mutex> l(m_);
    while (q_.size() >= cap_){
        cv_not_full_.wait(l);
    }
    q_.push(element);
    cv_not_empty_.notify_one();
}

template<typename T>
void BoundedBlockingQueue<T>::dequeue(T& element) {
    std::unique_lock<std::mutex> l(m_);
    while (q_.empty()){
        cv_not_empty_.wait(l);
    }
    element = q_.front();
    q_.pop();
    cv_not_full_.notify_one();
}

template<typename T>
size_t BoundedBlockingQueue<T>::size() const {
    std::unique_lock<std::mutex> l(m_);
    return q_.size();
}

template<typename T>
bool BoundedBlockingQueue<T>::empty() const {
    std::unique_lock<std::mutex> l(m_);
    return q_.empty();
}

template<typename T>
size_t BoundedBlockingQueue<T>::capacity() const {
    return cap_;
}

template<typename T>
bool BoundedBlockingQueue<T>::full() const {
    std::unique_lock<std::mutex> l(m_);
    return q_.size() >= cap_;
}
