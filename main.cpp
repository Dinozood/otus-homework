#include <iostream>
#include "ip_filter.h"
#include <cassert>
#include <cstdlib>

#include <algorithm>

int main() {
    try {
        std::vector<ip_addr> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ip_addr(split(v.at(0), '.')));
        }

        std::qsort(ip_pool.data(), ip_pool.size(), sizeof(ip_addr), ip_comp);


        for (auto ip: ip_pool) {
            ip.print();
        }

        for (auto ip: ip_pool) {
            if (ip._byte[0] == 1)
                ip.print();
        }

        for (auto ip: ip_pool) {
            if (ip._byte[0] == 46 && ip._byte[1] == 70)
                ip.print();
        }

        for (auto ip: ip_pool) {
            bool is_46 = false;
            for(auto byte : ip._byte) {
                if (byte == 46) {
                    is_46 = true;
                    break;
                }
            }
            if (is_46)
                ip.print();
        }

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
