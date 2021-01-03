//
// Created by wlx on 2021/1/2.
//

#ifndef CPLUSPLUS_CONCURRENT_RUNNABLE_H
#define CPLUSPLUS_CONCURRENT_RUNNABLE_H

#include <functional>


class Runnable {
public:
    Runnable();

    explicit Runnable(std::function<void()>  f);

    virtual ~Runnable();

    void run() const;

private:
    std::function<void()> f_;
};


#endif //CPLUSPLUS_CONCURRENT_RUNNABLE_H
