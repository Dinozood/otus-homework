#include <gtest/gtest.h>
#include "custom_allocator.h"
#include "Container.h"

#define UPPER_LIMIT (256)
#define DEFAULT_ALLOC_SIZE (10)

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
static void fill_map(Map &map) {
    for (int i = 0; i < DEFAULT_ALLOC_SIZE; ++i) {
        map[i] = fact(i);
    }
}

template<typename fw_lst>
static void fill_list(fw_lst &list) {
    for (int i = 0; i < DEFAULT_ALLOC_SIZE; ++i) {
        list.add(fact(i));
    }
}

template<typename Map>
static void fill_over_map(Map &map) {
    for (int i = 0; i < DEFAULT_ALLOC_SIZE + 1; ++i) {
        map[i] = fact(i);
    }
}

template<typename fw_lst>
static void fill_over_list(fw_lst &list) {
    for (int i = 0; i < DEFAULT_ALLOC_SIZE + 1; ++i) {
        list.add(fact(i));
    }
}

TEST(Allocator, ConstructionGood) {
    std::map<int, int, std::less<>, base_allocator<int, DEFAULT_ALLOC_SIZE>> map_with_custom;
    EXPECT_NO_THROW(fill_map(map_with_custom));
}

TEST(Allocator, ConstructionBad) {
    std::map<int, int, std::less<>, base_allocator<int, DEFAULT_ALLOC_SIZE>> map_with_custom;
    EXPECT_ANY_THROW(fill_over_map(map_with_custom));
}

TEST(CustomContainer, Filler) {
    forward_list<int> fwd_lst;
    fill_list(fwd_lst);
    forward_list<int>::Iterator iter(&fwd_lst);
    for (size_t i = 0; i < DEFAULT_ALLOC_SIZE; ++i) {
        EXPECT_EQ(iter->data, fact(i));
        ++iter;
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}