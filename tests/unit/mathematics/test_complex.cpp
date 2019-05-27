//
// Created by Spark on 25/02/2019.
//

#include <gtest/gtest.h>

#include <mathematics/complex.hpp>

TEST(UnitTestComplex, AssignmentOperatorAssignsTheReferencedObjectAndParameters)
{
    Complex a(3,5);
    Complex b(1,2);

    a = b;

    EXPECT_EQ(a.getReal(), b.getReal());
    EXPECT_EQ(a.getImag(), b.getImag());
}

TEST(UnitTestComplex, ComplexReturnsAbsoluteValues)
{
    Complex a(3,5);

    EXPECT_EQ(a.abs(), sqrt(34));
}
