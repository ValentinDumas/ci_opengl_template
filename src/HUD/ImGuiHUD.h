//
// Created by ValentinDU on 20/02/2018.
//

#ifndef DREAMINENGINE_IMGUIGLFWCONTEXT_H
#define DREAMINENGINE_IMGUIGLFWCONTEXT_H

#include <string>

class GLFWEnvironment;

class SceneManager;

typedef struct
{
	int x;
	int y;
	int w;
	int h;
} ImGuiWindowRect;

class ImGuiHUD {
public:
	ImGuiHUD(SceneManager &scene_manager, GLFWEnvironment *glfw_environment, bool install_callbacks);

	/* Init
	 * Initialize ImGui Context for a given GLFW environment
	 * @return -1 if GLFW context is not initialized
	 * @return -1 if gl3w cannot be initialized
	 * */
	int init();

	// Configure ImGui window(s) EVERY FRAME
	void update();

	// Render/Show the ImGui frame(s)
	void render();

	void close();

	void ShowMenubarMenuProject();

	void UpdateCurrentWindowRectData(ImGuiWindowRect* window_rect);

	// TODO: should be private
	// Window rectangle (frame limits)
	ImGuiWindowRect m_window_menubar;
	ImGuiWindowRect m_window_scene;
	ImGuiWindowRect m_window_entity;
	ImGuiWindowRect m_window_explorer;
	ImGuiWindowRect m_window_fileviewer;
private:
	SceneManager & m_scene_manager;
	GLFWEnvironment *m_glfw_environment;
	bool m_install_callbacks;

	// Debug windows
	bool m_show_demo_window;
	bool m_show_another_window;

	// DreamIn Engine main frames
	bool m_show_window_menubar;
	bool m_show_window_scene;
	bool m_show_window_entity;
	bool m_show_window_explorer;
	bool m_show_window_fileviewer;
};

#endif //DREAMINENGINE_IMGUIGLFWCONTEXT_H
