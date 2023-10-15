//
// Created by dinozood on 11.10.23.
//

#ifndef HOMEWORK_2_IP_FILTER_H
#define HOMEWORK_2_IP_FILTER_H

#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, char d);

typedef struct ip_addr {
    ip_addr();

    explicit ip_addr(std::vector<std::string> addr_line);
    void print() const;
    uint8_t _byte[4];
} ip_addr_ts;

int ip_comp(const void* L_v, const void* R_v);



#endif //HOMEWORK_2_IP_FILTER_H
