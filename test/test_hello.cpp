//
// Created by Spark on 15/02/2019.
//

#include <gtest/gtest.h>
#include <hello.h>

TEST(TestSuiteEquality, EQual)
{
    EXPECT_EQ(4, 4);
}

TEST(TestSuiteEquality, NonEQual)
{
    EXPECT_EQ(2,2);
}