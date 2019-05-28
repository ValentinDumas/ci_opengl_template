//
// Created by ValentinDU on 20/02/2018.
//

#include <SFML/OpenGL.hpp>
#include <GLFW/glfw3.h>
#include "GLFWEnvironment.h"

int window_position_x = 0; // from TOP LEFT of user's screen
int window_position_y = 0; // from TOP LEFT of user's screen
int window_width = 0; // Window with tilebar
int window_height = 0; // Window with tilebar

int frame_width = 0; // Window without tilebar
int frame_height = 0; // Window without tilebar
int is_focused = GLFW_FALSE; // Window (with tilebar) focused
int is_iconified = GLFW_FALSE; // Window iconified

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	frame_width = width;
	frame_height = height;
}

void window_focus_callback(GLFWwindow *window, int focused) {
	is_focused = focused;
}

void window_iconify_callback(GLFWwindow* window, int iconified)
{
	is_iconified = iconified;
}

void window_pos_callback(GLFWwindow* window, int xPos, int yPos)
{
	window_position_x = xPos;
	window_position_y = yPos;
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
}

void window_close_callback(GLFWwindow* window)
{

}

GLFWEnvironment::GLFWEnvironment(bool fullscreen, const std::string &title) {
	m_window = nullptr;
	m_title = title;
	m_width = 0; // defined later
	m_height = 0; // idem (in init())
	m_fullscreen = fullscreen;
}

GLFWEnvironment::GLFWEnvironment(const std::string &title, unsigned width, unsigned height, bool fullscreen) {
	m_window = nullptr;
	m_title = title;
	m_width = width;
	m_height = height;
	m_fullscreen = fullscreen;
	m_viewport_rect = { 0, 0, width, height };
}

std::vector<InputEnum> GLFWEnvironment::process_input() const {
	std::vector<InputEnum> inputs;
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_window, true);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		inputs.push_back(SPACE);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
		std::cout << "Z" << std::endl;
		inputs.push_back(ARROW_UP);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		std::cout << "S" << std::endl;
		inputs.push_back(ARROW_DOWN);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		std::cout << "D" << std::endl;
		inputs.push_back(ARROW_RIGHT);
	}
	else if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		std::cout << "Q" << std::endl;
		inputs.push_back(ARROW_LEFT);
	}
	return inputs;
}

int GLFWEnvironment::init() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::cout << "Error: Could not initialize GLFW !" << std::endl;
		return 1;
	}

	if (!m_width && !m_height) // Size undefined earlier
	{
		// Determine window size, based on screen resolution
		const GLFWvidmode *resolution = this->get_resolution();
		m_width = resolution->width;
		m_height = resolution->height;
		m_viewport_rect = {0, 0, m_width, m_height};
	}

#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150"; // Needed by ImGui
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
	// GL 3.0 + GLSL 130
	//const char* glsl_version = "#version 130"; // Needed by ImGui
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

	// NOTE: to display properly the window (with tilebar), 
	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), (m_fullscreen ? glfwGetPrimaryMonitor() : nullptr),
								nullptr);
	if (m_window == 0) {
		// Window or context creation failed
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_window);

	// Enable Vsync
	glfwSwapInterval(1);

	// Register callback functions
	glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), framebuffer_size_callback); // frame size
	glfwSetWindowFocusCallback(glfwGetCurrentContext(), window_focus_callback); // focus
	glfwSetWindowIconifyCallback(glfwGetCurrentContext(), window_iconify_callback); // iconify
	glfwSetWindowPosCallback(glfwGetCurrentContext(), window_size_callback); // window_size
	glfwSetWindowSizeCallback(glfwGetCurrentContext(), window_size_callback); // window size
	glfwSetWindowCloseCallback(glfwGetCurrentContext(), window_close_callback); // close

	// Replace (non-maximized/non-fullscreen) window to TOP LEFT origin
	int frame_top;
	glfwGetWindowFrameSize(glfwGetCurrentContext(), nullptr, &frame_top, nullptr, nullptr);
	glfwSetWindowPos(glfwGetCurrentContext(), 0, frame_top);

	// TODO : Loading those images should be the responsibility of the ResourceManager
	// Window icon & minified icon
//	GLFWimage icon[2];
//	icon[0].pixels = SOIL_load_image("resources/textures/pokeball.png", &icon[0].width, &icon[0].height, nullptr, SOIL_LOAD_RGBA);
//	icon[1].pixels = SOIL_load_image("resources/textures/container.jpg", &icon[1].width, &icon[1].height, nullptr, SOIL_LOAD_RGBA);
//	glfwSetWindowIcon(glfwGetCurrentContext(), 2, icon);
//	SOIL_free_image_data(icon[0].pixels);

	// Immediatly maximize window => fit the screen
	glfwMaximizeWindow(glfwGetCurrentContext());
}

void GLFWEnvironment::update_viewport(int x, int y, int width, int height) {
	m_viewport_rect.x = x;
	m_viewport_rect.y = y;
	m_viewport_rect.w = width;
	m_viewport_rect.h = height;
	//glViewport(m_viewport_rect.x, m_viewport_rect.y, m_viewport_rect.w, m_viewport_rect.h);
}

int GLFWEnvironment::quit() {
	return glfwWindowShouldClose(glfwGetCurrentContext());
}

GLFWwindow *GLFWEnvironment::get_window() {
	return glfwGetCurrentContext();
}

std::string &GLFWEnvironment::get_title() {
	return m_title;
}

int GLFWEnvironment::get_width() {
	
	return m_width = frame_width;
}

int GLFWEnvironment::get_height() {
	return m_height = frame_height;
}

void GLFWEnvironment::close() {
	glfwDestroyWindow(this->m_window); // Free allocated memory for window
	glfwTerminate(); // GlfW: terminate, clearing all previously allocated GLFW resources.
}

void GLFWEnvironment::clear_screen(float r, float g, float b, float a) {
//	glClearColor(r, g, b, a);
//	glClear(GL_COLOR_BUFFER_BIT);
}

bool GLFWEnvironment::is_fullscreen() {
	return m_fullscreen;
}

void GLFWEnvironment::set_fullscreen(bool fullscreen) {
	m_fullscreen = fullscreen;
}

const GLFWvidmode* GLFWEnvironment::get_resolution() const
{
	return glfwGetVideoMode(glfwGetPrimaryMonitor());
}

int GLFWEnvironment::get_window_position_x()
{
	return window_position_x;
}

int GLFWEnvironment::get_window_position_y()
{
	return window_position_y;
}

int GLFWEnvironment::get_window_width()
{
	return window_width;
}

int GLFWEnvironment::get_window_height()
{
	return window_height;
}

bool GLFWEnvironment::is_window_focused()
{
	return is_focused;
}

bool GLFWEnvironment::is_window_iconified()
{
	return is_iconified;
}