//
// Created by Spark on 15/02/2019.
//

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"
using ::testing::AtLeast;

TEST(TestSuiteEquality, EQual)
{
    EXPECT_EQ(4, 4);
}

TEST(TestSuiteEquality, NonEQual)
{
    EXPECT_EQ(2,2);
}

int test_unit_main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    int run_status = RUN_ALL_TESTS();

    return run_status;
}
