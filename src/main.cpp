#include "hello.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/// Main program function
int main(int argc, char **argv)
{
    int width, height;
    GLFWwindow* window;

    /* Init GLFW */
    if( !glfwInit() )
        exit( EXIT_FAILURE );

    window = glfwCreateWindow( 400, 400, "Boing (classic Amiga demo)", NULL, NULL );
    if (!window)
    {
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwSetWindowAspectRatio(window, 1, 1);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );

    glfwGetFramebufferSize(window, &width, &height);

    if(!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }
    printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    std::cout << "Setup status: SUCCESS" << std::endl;
    // std::cin.get();

    return 0;
}
