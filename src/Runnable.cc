//
// Created by wlx on 2021/1/2.
//

#include "Runnable.h"

Runnable::Runnable() = default;

Runnable::~Runnable() = default;

Runnable::Runnable(std::function<void()> f)
        : f_(std::move(f)) {
}

void Runnable::run() const {
    f_();
}
