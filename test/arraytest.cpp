#include "gtest/gtest.h"

#include "array.h"

TEST(ArrayTest, SizeTest) {
    auto arr = new Array();
    EXPECT_EQ(arr->size(), 0);
}