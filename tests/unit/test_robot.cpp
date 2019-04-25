//
// Created by Spark on 22/02/2019.
//

#include <gtest/gtest.h>

TEST(TestSuiteBis, NonBis)
{
    EXPECT_EQ(8,8);
}

TEST(TestSuiteEquality, EQual)
{
    EXPECT_EQ(4, 4);
}

TEST(TestSuiteEquality, NonEQual)
{
    EXPECT_EQ(2,2);
}
