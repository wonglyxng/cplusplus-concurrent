//
// Created by wlx on 2020/12/22.
//

#include <iostream>
#include <gtest/gtest.h>
#include "Utils.h"

TEST(Utils, getLocalIps) // NOLINT
{
    auto ips = getLocalHostIPs();
    for(auto &ip: ips){
        std::cout << ip << std::endl;
    }
}