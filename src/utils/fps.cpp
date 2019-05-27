//
// Created by Spark on 07/05/2019.
//

#include "fps.h"

#include <GLFW/glfw3.h>

#include <iostream>

double lastTimeFPS = glfwGetTime();
unsigned int nbFrames = 0;

void utils::get_fps()
{
    // Measure speed
    const double currentTimeFPS = glfwGetTime();

    nbFrames++;

    if (currentTimeFPS - lastTimeFPS >= 1.0) { // each second
        std::cout << nbFrames << " FPS (" << 1000.0 / double(nbFrames) << "ms/frame)" << std::endl;
        nbFrames = 0;
        lastTimeFPS += 1.0;
    }
}