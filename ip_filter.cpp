#include <iostream>
#include <string>
#include <vector>
#include "ip_filter.h"


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}

int ip_comp(const void *L_v, const void *R_v) {
    ip_addr L = *static_cast<const ip_addr *>(L_v);
    ip_addr R = *static_cast<const ip_addr *>(R_v);
    for (size_t i = 0; i < sizeof(L._byte); ++i) {
        if (L._byte[i] != R._byte[i]) {
            if (L._byte[i] < R._byte[i])
                return 1;
            else
                return -1;
        }
    }
    return 0;
};

ip_addr::ip_addr(std::vector<std::string> addr_line) {
    if (addr_line.size() != sizeof(_byte))
        throw std::invalid_argument("Can't parse IP addr");
    decltype(std::stoi("")) err_checker;
    for (size_t i = 0; i < addr_line.size(); ++i) {
        err_checker = std::stoi(addr_line[i]);
        if ((err_checker > 255) ||
            (err_checker < 0))
            throw std::invalid_argument("Can't parse IP addr. IP addr can contains numbers between 0 and 255");
        _byte[i] = err_checker;
    }
}

void ip_addr::print() const {
    for (size_t i = 0; i < sizeof(_byte); ++i) {
        if (i != 0)
            std::cout << '.';
        std::cout << (int) _byte[i];
    }
    std::cout << std::endl;
}

ip_addr::ip_addr() {

}
