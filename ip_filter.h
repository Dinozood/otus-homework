//
// Created by dinozood on 11.10.23.
//

#ifndef HOMEWORK_2_IP_FILTER_H
#define HOMEWORK_2_IP_FILTER_H

#include <vector>
#include <string>
#include <array>


std::vector<std::string> split(const std::string &str, char d);


typedef struct ip_addr {
    ip_addr();

    explicit ip_addr(std::vector<std::string> addr_line);

    void print() const;

    std::array<uint8_t, 4> _byte;
} ip_addr_ts;


#endif //HOMEWORK_2_IP_FILTER_H
