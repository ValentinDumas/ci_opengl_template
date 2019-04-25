//
// Created by Spark on 20/02/2019.
//

#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::AtLeast;

#include "mathematics/complex.hpp"

int test_integration_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    int integration_test_status = RUN_ALL_TESTS();

    Complex a(3,5);
    Complex b(3,0);
    Complex c(a);
    std::cout << a.getReal() << " " << a.getImag() << " " << a.abs() << std::endl;
    std::cout << b.getReal() << " " << b.getImag() << " " << b.abs() << std::endl;
    std::cout << c.getReal() << " " << c.getImag() << " " << c.abs() << std::endl;

    return integration_test_status;
}
