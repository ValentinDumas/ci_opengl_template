//
// Created by Spark on 25/02/2019.
//

#include <complex.hpp>
#include <gtest/gtest.h>

#include "glm/glm.hpp"

TEST(UnitTestComplex, AssignmentOperatorAssignsTheReferencedObjectAndParameters)
{
	glm::mat4 allo(1.0f);

    Complex a(3,5);
    Complex b(1,2);

    a = b;

    EXPECT_EQ(a.getReal(), b.getReal());
    EXPECT_EQ(a.getImag(), b.getImag());
}
