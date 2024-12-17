#include <gtest/gtest.h>
#include "shared.h"


class Something
{
public:
    int returnZero()
    {
        return 0;
    }
};


TEST(UniquePtrTest, UseCount)
{
    SharedPtr<int> ptr(new int(50));
    EXPECT_EQ(ptr.use_count(), 1);

    SharedPtr<int> ptr2 = ptr;
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(UniquePtrTest, UseCount1)
{
    SharedPtr<int> ptr(new int(50));
    EXPECT_EQ(ptr.use_count(), 1);

    SharedPtr<int> ptr2;
    ptr2 = ptr;
    EXPECT_EQ(ptr2.use_count(), 2);
}