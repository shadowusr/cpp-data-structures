#include <cmath>
#include <iostream>
#include "gtest/gtest.h"

#include "array.h"
#include "array.cpp"

TEST(ArrayTest, DefaultConstructorTest) {
    auto arr = Array<int>();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(ArrayTest, SizeConstructorTest) {
    auto arr = Array<int>(5);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.capacity(), 5);

    for (int i = 0; i < 5; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ArrayTest, FillConstructorTest) {
    auto arr = Array<double>(10, -1.5);
    EXPECT_EQ(arr.size(), 10);
    EXPECT_EQ(arr.capacity(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr[i], -1.5);
    }
}

TEST(ArrayTest, SizeTest) {
    auto arr = Array<int>(0);
    EXPECT_EQ(arr.size(), 0);

    for (int i = 0; i < 10; i++) {
        arr.push(i);
    }

    EXPECT_EQ(arr.size(), 10);

    arr.pop();
    arr.erase(0);
    arr.remove(7);
    arr.remove(-1);

    EXPECT_EQ(arr.size(), 7);

    arr.unshift(0);
    arr.insert(1, -1);

    EXPECT_EQ(arr.size(), 9);
}

TEST(ArrayTest, CapacityTest) {
    auto arr = Array<int>(0);
    EXPECT_EQ(arr.capacity(), 0);

    arr.push(1);
    EXPECT_EQ(arr.capacity(), 1);

    arr.push(2);
    arr.push(3);
    EXPECT_EQ(arr.capacity(), 4);

    arr.clear();
    EXPECT_EQ(arr.capacity(), 0);

    for (int i = 0; i < 70; i++) {
        arr.push(i);
    }

    EXPECT_EQ(arr.capacity(), 128);

    for (int i = 0; i < 40; i++) {
        arr.pop();
    }

    EXPECT_EQ(arr.capacity(), 64);

    arr = Array<int>(3);
    EXPECT_EQ(arr.capacity(), 3);

    arr.insert(1, -1);
    EXPECT_EQ(arr.capacity(), 6);
}

TEST(ArrayTest, IsEmptyTest) {
    auto arr = Array<int>(0, 1);
    EXPECT_EQ(arr.isEmpty(), true);

    arr.push(1);
    arr.insert(0, -1);
    EXPECT_EQ(arr.isEmpty(), false);

    arr.remove(-1);
    arr.erase(0);
    EXPECT_EQ(arr.isEmpty(), true);
}

TEST(ArrayTest, PushTest) {
    auto arr = Array<int>();
    arr.push(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 0);

    for (int i = 1; i <= 10; i++) {
        arr.push(i);
    }

    EXPECT_EQ(arr.size(), 11);

    for (int i = 0; i <= 10; i++) {
        EXPECT_EQ(arr[i], i);
    }

    arr.pop();
    arr.pop();
    arr.push(1000);
    EXPECT_EQ(arr[9], 1000);
    EXPECT_EQ(arr.size(), 10);
}

TEST(ArrayTest, InsertTest) {
    auto arr = Array<int>();
    arr.insert(0, -1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], -1);
    arr.clear();

    for (int i = 1; i <= 10; i++) {
        arr.push(i * 2);
    }

    for (int i = 0; i < 10; i++) {
        arr.insert(i * 2, i * 2 + 1);
    }

    EXPECT_EQ(arr.size(), 20);

    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(arr[i], i + 1);
    }

    arr = Array<int>(5, -1);
    for (int i = 0; i < 5; i++) {
        arr.insert(i * 2, 1);
    }

    EXPECT_EQ(arr.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ((i & 1 && arr[i] < 0) || (!(i & 1) && arr[i] > 0), true);
    }
}

TEST(ArrayTest, UnshiftTest) {
    auto arr = Array<int>();
    arr.push(3);
    arr.push(4);
    arr.unshift(2);
    arr.unshift(1);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

TEST(ArrayTest, PopTest) {
    auto arr = Array<int>();
    arr.push(6);
    arr.push(8);
    arr.push(10);
    arr.unshift(4);
    arr.unshift(2);

    for (int i = 0; i < 5; i++) {
        arr.insert(i * 2, i * 2 + 1);
    }

    for (int i = 10; i >= 1; i--) {
        EXPECT_EQ(arr.pop(), i);
    }

}

TEST(ArrayTest, EraseTest) {
    auto arr = Array<int>(10);

    for (int i = 0; i < 10; i++) {
        arr[i] = i + 1;
    }

    arr.erase(8);
    arr.erase(6);
    arr.erase(4);
    arr.erase(2);
    arr.erase(0);

    EXPECT_EQ(arr.size(), 5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], (i + 1) * 2);
    }
}

TEST(ArrayTest, RemoveTest) {
    auto arr = Array<int>(10, -1);

    for (int i = 3; i <= 6; i++) {
        arr[i] = i;
    }

    arr.remove(-1);
    EXPECT_EQ(arr.size(), 4);

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], i + 3);
    }

}

TEST(ArrayTest, FindTest) {
    auto arr = Array<int>(20);

    for (int i = 0; i < 20; i++) {
        arr[i] = i;
    }

    EXPECT_EQ(arr.find(-1), arr.end());
    EXPECT_EQ(arr.find(20), arr.end());

    for (int i = 0; i < 20; i++) {
        EXPECT_EQ(*(arr.find(i)), i);
    }
}

TEST(ArrayTest, ClearTest) {
    auto arr = Array<int>(20, -1);
    arr.clear();
    EXPECT_EQ(arr.size(), 0);

    for (int i = 0; i < 10; i++) {
        arr.push(i);
    }
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, IndexingOperatorTest) {
    auto arr = Array<int>(10, -1);
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr[i], i);
    }

    arr[2] = 19;
    EXPECT_EQ(arr[2], 19);
    arr[2]++;
    EXPECT_EQ(arr[2], 20);
}

TEST(ArrayTest, CopyAssignmentOperatorTest) {
    auto arr = Array<int>(10);
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    auto arr2 = Array<int>();

    arr2 = arr;
    arr.clear();

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr2[i], i);
    }
}

TEST(ArrayTest, CopyConstructorTest) {
    auto arr = Array<int>(10);
    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    auto arr2 = arr;
    arr.clear();

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr2[i], i);
    }
}

TEST(ArrayTest, MoveConstructorTest) {
    auto arr = Array<int>();
    for (int i = 0; i < 10; i++) {
        arr.push(i);
    }

    int size = arr.size(), capacity = arr.capacity();
    auto arr2 = std::move(arr);

    EXPECT_EQ(size, arr2.size());
    EXPECT_EQ(capacity, arr2.capacity());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr2[i], i);
    }
}

TEST(ArrayTest, MoveAssignmentOperatorTest) {
    auto arr = Array<int>();
    for (int i = 0; i < 10; i++) {
        arr.push(i);
    }

    int size = arr.size(), capacity = arr.capacity();
    auto arr2 = Array<int>();
    arr2 = std::move(arr);

    EXPECT_EQ(size, arr2.size());
    EXPECT_EQ(capacity, arr2.capacity());
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(arr2[i], i);
    }
}