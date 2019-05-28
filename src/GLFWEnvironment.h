//
// Created by ValentinDU on 20/02/2018.
//

#ifndef DREAMINENGINE_GLFWENVIRONMENT_H
#define DREAMINENGINE_GLFWENVIRONMENT_H

#include <iostream>
#include <glm/detail/type_vec2.hpp>

#include "utils/InputEnum.h"
#include <vector>

struct GLFWwindow;

struct GLFWvidmode;

typedef struct
{
	int x;
	int y;
	unsigned int w;
	unsigned h;
} ViewportRect;

// Include Windows
#ifdef WIN32

// Include Mac
#elif __APPLE__
// #define GL3_PROTOTYPES 1
// #include <OpenGL/gl3.h>

// Include UNIX/Linux
// #else
// #define GL3_PROTOTYPES 1
// #include <GL3/gl3.h>
#endif

static void error_callback(int error, const char *description) {
	fprintf(stderr, "Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class GLFWEnvironment {
public:
	GLFWEnvironment(bool fullscreen = false, const std::string &title = "DreamIn Engine");

	GLFWEnvironment(const std::string &title, unsigned width, unsigned height, bool fullscreen = false);

	// TODO: move this apart cause it might not be its responsibilty (to manage inputs)
	std::vector<InputEnum> process_input() const;

	int init();

	void update_viewport(int x, int y, int width, int height);

	void clear_screen(float r, float g, float b, float a);

	int quit();

	void close();

	GLFWwindow *get_window();

	std::string &get_title();

	int get_width(); // get FRAME width (without toolbar)

	int get_height(); // get FRAME with (without toolbar)

	bool is_fullscreen();

	void set_fullscreen(bool fullscreen);

	const GLFWvidmode* get_resolution() const;

	int get_window_position_x();

	int get_window_position_y();

	int get_window_width();

	int get_window_height();

	bool is_window_focused();

	bool is_window_iconified();

private:
    GLFWwindow * m_window;
    std::string m_title;
    unsigned m_width;
    unsigned m_height;
    bool m_fullscreen = true;
    ViewportRect m_viewport_rect;
};

#endif //DREAMINENGINE_GLFWENVIRONMENT_H
