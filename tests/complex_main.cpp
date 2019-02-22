//
// Created by Spark on 20/02/2019.
//

#include <iostream>

#include "complex.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::AtLeast;

TEST(TestCaseSuite, TestRien)
{
    EXPECT_EQ(1, 1);
}

int main_tests(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    int run_status = RUN_ALL_TESTS();

    Complex a(3,5);
    Complex b(3,0);
    Complex c(a);

    std::cout << a.getReal() << " " << a.getImag() << " " << a.abs() << std::endl;
    std::cout << b.getReal() << " " << b.getImag() << " " << b.abs() << std::endl;
    std::cout << c.getReal() << " " << c.getImag() << " " << c.abs() << std::endl;

    return run_status;
}