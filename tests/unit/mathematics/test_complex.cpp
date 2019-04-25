//
// Created by Spark on 25/02/2019.
//

#include <gtest/gtest.h>

#include <glm/glm.hpp>

#include <mathematics/complex.hpp>

TEST(UnitTestComplex, AssignmentOperatorAssignsTheReferencedObjectAndParameters)
{
	glm::mat4 allo(1.0f);

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
