#include "ip_filter.h"
#include <gtest/gtest.h>

#define UPPER_LIMIT (256)

void test_all_good() {
    /*
     * testing 2^64 variants is too much as for me
     * */

    std::srand(std::time(nullptr));
    for (int i = 0; i < 10000; ++i) {
        std::vector<std::string> tmp = {
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
        };
        ip_addr exmpl(tmp);
    }
}


TEST(IpValidation, dontCatchExpressionsInFor) {
    EXPECT_NO_THROW(test_all_good());
}

TEST(IpValidation, catchIt) {
    for (int i = 0; i < 1000; ++i) {
        std::srand(std::time(nullptr));
        std::vector<std::string> ipAddr = {
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
                std::to_string(std::rand() % UPPER_LIMIT),
        };
        ipAddr[std::rand() % 4] = std::to_string((std::rand() % UPPER_LIMIT) + UPPER_LIMIT);
        EXPECT_ANY_THROW([[maybe_unused]] ip_addr tmp1 = ip_addr(ipAddr));
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}