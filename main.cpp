#include <iostream>
#include <cassert>
#include <cstdlib>

#include <algorithm>
#include <map>

#include "custom_allocator.h"
#include "Container.h"

static uint16_t fact(uint16_t n) {
    long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    return factorial;
}

template<typename Map>
static void print_it(const Map &map) {
    for (auto pair: map) {
        std::cout << (int) pair.first << " " << (int) pair.second << std::endl;
    }
    std::cout << std::endl;
}

template<typename Map>
static void fill_map(Map& map) {
    for (int i = 0; i < 10; ++i) {
        map[i] = fact(i);
    }
}

template<typename fw_lst>
static void fill_list(fw_lst& list) {
    for (int i = 0; i < 10; ++i) {
        list.add(fact(i));
    }
}




int main() {
    try {
        std::map<int, int> int_map;
        fill_map(int_map);
        print_it(int_map);

        std::map<int, int, std::less<int>, base_allocator<int>> int_map_alloc;
        fill_map(int_map_alloc);
        print_it(int_map_alloc);

        forward_list<int> int_list;
        fill_list(int_list);
        std::cout << int_list << std::endl << std::endl;

        forward_list<int, base_allocator<int>> int_list_alloc;
        fill_list(int_list_alloc);
        std::cout << int_list_alloc << std::endl;

    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
