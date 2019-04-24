//
// Created by Spark on 22/02/2019.
//

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

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

TEST(TestSuiteGLFW, GLFWInitializationIsASuccess)
{
    int glfw_init_status = glfwInit();
    int expected_glfw_init_status = GLFW_TRUE;
    EXPECT_EQ(glfw_init_status, expected_glfw_init_status);
}