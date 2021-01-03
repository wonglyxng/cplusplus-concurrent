//
// Created by wlx on 2020/12/22.
//

#include "Utils.h"

#ifdef _WIN32
#else
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

#endif

std::vector<std::string> getLocalHostIPs() {
    std::vector<std::string> localIps;
#ifdef _WIN32
#else
    struct ifaddrs *ifList;

    if (getifaddrs(&ifList) == -1) {
        perror("getifaddrs error");
        return localIps;
    }

    for (auto ifa = ifList; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) {
            // is a valid IP4 Address
            auto addr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, addr, ip, INET_ADDRSTRLEN);
            localIps.emplace_back(ip);
        } else if (ifa->ifa_addr->sa_family == AF_INET6) {
            // is a valid IP6 Address
            auto addr = &((struct sockaddr_in6 *) ifa->ifa_addr)->sin6_addr;
            char ip[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, addr, ip, INET6_ADDRSTRLEN);
            localIps.emplace_back(ip);
        }
    }

    if (ifList) {
        freeifaddrs(ifList);
    }
#endif
    return localIps;
}