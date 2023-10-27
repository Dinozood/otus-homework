#include <iostream>
#include "ip_filter.h"
#include <cassert>
#include <cstdlib>

#include <algorithm>

template<class Filter>
void filter_print(const std::vector<ip_addr> &pool, Filter filter) {
    for (auto ip: pool) {
        if (filter(ip))
            ip.print();
    }
};

int main() {
    try {
        std::vector<ip_addr> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ip_addr(split(v.at(0), '.')));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](ip_addr &L, ip_addr &R) -> bool {
            return (L._byte >= R._byte);
        });

        std::vector<std::function<bool(ip_addr ip)>> filters{
                [](const ip_addr ip) {
                    (void) ip;
                    return true;
                },
                [](const ip_addr ip) { return (ip._byte[0] == 1); },
                [](const ip_addr ip) { return (ip._byte[0] == 46 && ip._byte[1] == 70); },
                [](const ip_addr ip) {
                    return std::any_of(ip._byte.begin(), ip._byte.end(), [](uint8_t byte) -> bool {
                        return (byte == 46);
                    });
                }

        };

        for (auto filter: filters)
            filter_print(ip_pool, filter);

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
