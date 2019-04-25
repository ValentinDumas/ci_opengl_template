//
// Created by Spark on 15/02/2019.
//

#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::AtLeast;

int test_unit_main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    int unit_test_status = RUN_ALL_TESTS();

    return unit_test_status;
}
