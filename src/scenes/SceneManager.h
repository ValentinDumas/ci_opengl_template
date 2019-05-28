//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_SCENEMANAGER_H
#define DREAMINENGINE_SCENEMANAGER_H

/** NOTE: [Sprite <=> Texture + Position(s)]
 *  Sprite might be a mix of Texture and vertices/indices/text_coords,
 *  grouped together in a single structure
 */

 /** NOTE: 5 differents cordinate systems:
  * Local space (or Object space)
  * World space
  * View space (or Eye space)
  * Clip space
  * Screen space
  */

  // @TODO: Move those "deprecated includes"
#include <scenes/Scene.h>
#include <SpriteRenderer.h>

#include <utils/RunningConfigEnum.h>

bool has_component(unsigned int entity_mask, unsigned int component_mask);
class ImGuiHUD;

class SpriteRenderer;

class GLFWEnvironment;

typedef enum
{
	PROJECTION_NORMALIZED_TOP_LEFT = 0,  // Normalized, Default 2D projection
	PROJECTION_NORMALIZED_CENTER_CENTER = 1, // Normalized, but textures have reverse coordinates
	PROJECTION_CENTER_CENTER = 2, // No projection
} ProjectionType;

typedef enum : unsigned int
{
	COMPONENT_NONE = 0,
	COMPONENT_SPRITE = 1 << 0,
	COMPONENT_BOX2DPHYSICS = 1 << 1,
	COMPONENT_INPUT = 1 << 2,
	COMPONENT_TOTAL = 1 << 3,
} ComponentType;

typedef struct BooleanCustom
{
	BooleanCustom() : Result(false), Message("") { }
	BooleanCustom(bool result, std::string message) : Result(result), Message(std::move(message)) { }
	bool Result;
	std::string Message;
} BooleanCustom;

class SceneManager {

private:
	/* Environments, Texture & Shader Loaders */
	GLFWEnvironment * m_glfw_environment;
	ImGuiHUD *m_ImGui_HUD;

	/* Locations & Matrices */
	Scene *m_active_scene;
	std::vector<Scene *> m_scenes;
	std::unordered_map<std::string, unsigned int> m_index_scene;

	SpriteRenderer *spriteRenderer;

	RunningConfigEnum m_runningConfigEnum;
public:

	SceneManager(GLFWEnvironment *glfw_environment);

	/* Start
	 * Begins SceneManager's initialization process.
	 * If the initialization is successful, runs its content */
	void start();

	/* Init
	 * Initialize this manager's GL, GLFW and ImGUI context
	 * Also initialize a shader manager and a texture loader
	 * Returns true if the initialization was successful, otherwise it returns false */
	bool init();

	/* Run
	 * Run this manager to start updating and rendering */
	void run() const;

	/* Create Scene
	 * Create a new scene with a given name
	 * The newly created scene is added to the SceneManager's scene pool */
	void createScene(const std::string &nameScene);

	//@TODO: check if the name corresponds to an existant scene: if not, returns a false boolean value with an error message
	/* Select Scene
	 * Select the scene with the given name
	 * [...] */
	void select_scene(const std::string &nameScene);

	void select_first_scene();

	//@TODO: Idem
	/* Change Scene Name
	 * Modify the name of the scene
	 * [...] */
	void changeSceneName(std::string oldName, std::string newName);

	//@TODO: Idem
	/* Erase Scene
	 * Erase the scene which has the good name */
	void eraseScene(std::string nameScene);

	//@TODO: Idem
	/* Get Scene
	 * Call a scene by its name
	 * [...] */
	Scene *getScene(std::string nameScene);

	/* Get Scenes
	 * Get all the scenes from this manager */
	std::vector<Scene *> getScenes() const;

	/* Get Actual Scene
	 * Get selected / active scene for this manager */
	Scene* active_scene() const;

	/* Get Index Scene
	 * Get a Scene's index from a name */
	std::unordered_map<std::string, unsigned int> getIndexScene() const;

	/* New Sprite
	 * Adds a New Sprite to a specific scene */ // TODO: change this fucking default value
	void new_sprite(unsigned int entity_id, Texture texture = ResourceManager::GetTexture("container"), glm::vec2 position = glm::vec2(50.0f, 50.0f));

	/* Update Sprite
	 * Updates a specific sprites thanks to OpenGL
	 * This method is directly called by one or more scene(s) */
	void update_sprite(Sprite *sprite);

	/* Render Sprite
	 * Renders a specific sprites at the screen thanks to OpenGL
	 * This method is directly called by one or more scene(s) */
	void render_sprite(Sprite *sprite);

	// @NOTE: For Real-Time Game modification
	void addBox2D(Entity *entity, Sprite *sprite, bool dynamicBody);

	void addInput(Entity *entity);

	void setRunningConfigEnum(RunningConfigEnum rce) { m_runningConfigEnum = rce; }
	RunningConfigEnum getRunningConfigEnum() const { return m_runningConfigEnum; }

	BooleanCustom add_component(unsigned int component_type, unsigned int entity_id);

	template<typename T>
	T* get_component(ComponentType component_type, unsigned int entity_id);

	// TODO: get components for 1 entity
	std::vector<unsigned int> get_components(unsigned int entity_id);

	void add_entity(std::string name, float x = 50.0f, float y = 50.0f);

	void remove_entity(unsigned int id);

	bool remove_component(unsigned int id, unsigned int component);

	bool remove_components(unsigned int id);

	~SceneManager();
};

#endif //DREAMINENGINE_SCENEMANAGER_H
