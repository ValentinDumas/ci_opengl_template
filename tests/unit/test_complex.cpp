//
// Created by Spark on 25/02/2019.
//

#include <complex.hpp>
#include <gtest/gtest.h>

TEST(UnitTestComplex, AssignmentOperatorAssignsTheReferencedObjectAndParameters)
{
    Complex a(3,5);
    Complex b(1,2);

    a = b;

    EXPECT_EQ(a.getReal(), b.getReal());
    EXPECT_EQ(a.getImag(), b.getImag());
}
