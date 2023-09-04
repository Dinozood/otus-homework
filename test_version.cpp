#include "lib.h"
#include <gtest/gtest.h>

TEST(ProjectVersionTest, SuitableVersion) {
    EXPECT_GT(version(), 0);
}