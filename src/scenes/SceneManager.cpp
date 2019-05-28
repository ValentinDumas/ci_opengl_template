//
// Created by Thomas Bisson and Valentin Dumas on 30/01/2018.
//

#include <HUD/ImGuiHUD.h>

#include <glad/glad.h>
#include <GLFWEnvironment.h>
#include <GLFW/glfw3.h>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include "utils/fps.h"
#include <utility>

#define IDENTITY_MATRICE 1.0f

static int ID = 0;

SceneManager::SceneManager(GLFWEnvironment *glfw_environment) {
	m_glfw_environment = glfw_environment;
	m_ImGui_HUD = new ImGuiHUD(*this, glfw_environment, true);
	m_ImGui_HUD->init();

	m_active_scene = nullptr;

	m_scenes = std::vector<Scene *>(0);
	m_index_scene = std::unordered_map<std::string, unsigned int>();

	m_runningConfigEnum = CONFIG;

	// TODO: Init projection mat4 ARRAY on the gpu side ! and call rendering to the good projection thanks to the enum id
	// TODO: also see how to do a GLSL array (especially for mat4 arrays)
	// Configure shaders
	// 
	glm::mat4 projections[] = {
		glm::ortho(0.0f, static_cast<GLfloat>(glfw_environment->get_width()), static_cast<GLfloat>(glfw_environment->get_height()), 0.0f, -1.0f, 1.0f), // Normalized TOP LEFT
		glm::ortho(static_cast<GLfloat>((-m_glfw_environment->get_width()) / 2), static_cast<GLfloat>(m_glfw_environment->get_width() / 2), static_cast<GLfloat>(-m_glfw_environment->get_height() / 2), static_cast<GLfloat>(m_glfw_environment->get_height() / 2), -1.0f, 1.0f) // Normalized CENTER CENTER
	 };

	// NOTE: the call is written as "API friendly" => Easier to configure the shader (and faster !)
	// e.g. here, only one static call to "GetShader", instead of 4 !
	ResourceManager::GetShader("sprite2D").Use()
		.SetInteger("image", 0)
		.SetInteger("projectionType", PROJECTION_NORMALIZED_TOP_LEFT)
		.SetMatrix4("projection", projections[PROJECTION_NORMALIZED_TOP_LEFT]);

	// Load Renderers
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite2D"));
}

bool SceneManager::init() {
	bool success = true;

	/* Create entity */
	add_entity("container_entity");
	add_entity("face_entity");
	add_entity("pokeball_entity");

	this->add_component(COMPONENT_BOX2DPHYSICS, 0);

	// Face (Entity ID: 1)
	this->get_component<Sprite>(COMPONENT_SPRITE, 1)->m_texture = ResourceManager::GetTexture("awesomeface");
	this->get_component<Sprite>(COMPONENT_SPRITE, 1)->Position = glm::vec2(50.0, 300.0f);
	this->add_component(COMPONENT_INPUT, 1);

	// Pokeball (Entity ID: 2)
	this->get_component<Sprite>(COMPONENT_SPRITE, 2)->m_texture = ResourceManager::GetTexture("pokeball");
	this->get_component<Sprite>(COMPONENT_SPRITE, 2)->Position = glm::vec2(50.0, 500.0f);

	//this->get_components(0); // entity 0's component mask

	// [CRITICAL] TODO: solve the case where a component (ex: Sprite) can't be updated (Position/Rotation/etc..) while having an attached Box2D collider

	return success;
}

void SceneManager::start() {
	if (!init()) {
		std::cout << "Error: Could not initialize SceneManager [init error]" << std::endl;
		return;
	}
	run();
}

void SceneManager::run() const {
	while (!m_glfw_environment->quit()) {

		utils::get_fps();

		glfwPollEvents();

		std::vector<InputEnum> inputs = m_glfw_environment->process_input(); // Order ??

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// TODO: Trigger a viewPort update => Update Scene(s) frame to fit the screen
		// TODO: Create window explorer at the bottom of the screen
		// TODO: Add window explorer to viewport's height calculation(s)
		// [IMPORTANT WARNING]: Viewport & Scissor have their ORIGIN (0;0) to LOWER LEFT ! 
		int x = m_ImGui_HUD->m_window_scene.w; // + (m_ImGui_HUD->m_window_scene.x); This one is for responsive design
		int y = m_ImGui_HUD->m_window_explorer.h + (m_glfw_environment->get_height() * 0.030f); // optional, only to have square textures
		unsigned int width = m_ImGui_HUD->m_window_entity.x - x; // NOTE: Not very reliable..
		unsigned int height = (m_glfw_environment->get_height() - m_ImGui_HUD->m_window_explorer.h) - m_ImGui_HUD->m_window_menubar.h - (m_glfw_environment->get_height() * 0.060f); // *0.035f to have square textures

		// TODO: Improve OpenGL render scene frame (responsiveness);
		// Hmax = Lmax * (Rhauteur / Rlargeur); = width * (1080 / 1920);
		//height = width * 9 / 16;


		// NOTE: (Re)Define the zone where OpenGL can Draw/Render things
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, y, width, height); // Redefine the OpenGL's drawable zone
		glViewport(x, y, width, height);
		glClearColor(0.6f, 0.6f, 0.6f, 1.0f); // Clear only the defined zone
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		//glColor3d(1, 0, 0);
		//glBegin(GL_QUADS);
		//glVertex2f(0.0f, 10.0f); // top left
		//glVertex2f(10.0f, 10.0f); // top right 
		//glVertex2f(10.0f, -0.0f); // bottom right
		//glVertex2f(-0.0f, -0.0f); // bottom left

		//glEnd();

		m_ImGui_HUD->update();

		if (m_active_scene) // Selected scene
		{
			if (RUNNING == m_runningConfigEnum) {
				m_active_scene->update(inputs);
			}

			// TODO: Test MultiRendering from different views/(<=>viewports)/perspectives
			m_active_scene->render();
		}
		else // No scene selected
		{
		}

		m_ImGui_HUD->render();

		// TODO: From GLFW ?
		glfwSwapBuffers(m_glfw_environment->get_window());

		// TODO: call this from GLFWEnvironment (adapt the calling update_viewport method ?)
		glViewport(0, 0, m_glfw_environment->get_width(), m_glfw_environment->get_height());
	}

	// Cleanup
	m_ImGui_HUD->close();
	m_glfw_environment->close();
}

void SceneManager::createScene(const std::string &nameScene) {
	m_scenes.emplace_back(new Scene(this, nameScene));
	m_index_scene[nameScene] = m_scenes.size() - 1;
}

void SceneManager::select_scene(const std::string &nameScene)
{
	for (auto& scene : m_scenes)
	{
		if (scene->getName() == nameScene)
		{
			m_active_scene = scene;
			break;
		}

		// NOTE: no scene found
	}
}

void SceneManager::select_first_scene()
{
	if(m_scenes.empty())
	{
		std::cout << "Cannot select first scene (empty scene list)" << std::endl;
		return;
	}

	m_active_scene = m_scenes[0];
}

void SceneManager::changeSceneName(std::string oldName, std::string newName) {
	//Change the name of the scene in the vector
	m_scenes[m_index_scene[oldName]]->setName(newName);

	//Change the key in the map
	std::unordered_map<std::string, unsigned int>::iterator i = m_index_scene.find(oldName);
	const unsigned int tmp = i->second;
	m_index_scene.erase(i);
	m_index_scene[newName] = tmp;
}

// Remove the scene from the vector
void SceneManager::eraseScene(std::string nameScene) {
	int i = m_index_scene[nameScene];
	m_scenes.at(i) = m_scenes[m_scenes.size() - 1];
	m_scenes.pop_back();

	//Remove the scene from the map
	std::unordered_map<std::string, unsigned int>::iterator it2;
	for (std::unordered_map<std::string, unsigned int>::iterator it = m_index_scene.begin();
		it != m_index_scene.end(); ++it) {
		int ii = it->second;
		if (ii == i) {
			it2 = it;
		}
		else if (ii > i) {
			it->second -= 1;
		}
	}
	m_index_scene.erase(it2);
}

Scene *SceneManager::getScene(std::string nameScene) {
	return m_scenes[m_index_scene[nameScene]];
}

std::vector<Scene *> SceneManager::getScenes() const { return m_scenes; }

Scene* SceneManager::active_scene() const {
	return m_active_scene;
}

std::unordered_map<std::string, unsigned int> SceneManager::getIndexScene() const { return m_index_scene; }

void SceneManager::new_sprite(unsigned int entity_id, Texture texture, glm::vec2 position) {
	Sprite *sprite = new Sprite(texture, position);

	/* Add newly created Sprite object to the specified Scene */
	this->active_scene()->add_sprite(entity_id, sprite);

	//delete sprite;
	//sprite = nullptr;
}

void SceneManager::update_sprite(Sprite *sprite) {
	//sprite->Position.x += 1;
}

void SceneManager::render_sprite(Sprite *sprite) {
	// TODO: Do mirror towards X-axis too...  => Make a struct to store the Axis
	spriteRenderer->DrawSprite(sprite->m_texture, sprite->Position, sprite->Size, sprite->Rotation, sprite->Color, GL_FALSE);
}

// TODO: move to another location
void SceneManager::addBox2D(Entity *entity, Sprite *sprite, bool dynamicBody) {
	m_active_scene->add_box_physics(entity, sprite->Position.x, sprite->Position.y,
		sprite->Size.x, sprite->Size.y, dynamicBody);
}

void SceneManager::addInput(Entity *entity) {
	m_active_scene->add_input(entity);
}

//@TODO: see if there is no memory leaks => Do Tests
SceneManager::~SceneManager() {
	delete m_ImGui_HUD;
	delete m_glfw_environment;
	delete spriteRenderer;

	m_ImGui_HUD = nullptr;
	m_glfw_environment = nullptr;
	spriteRenderer = nullptr;

	/*for (auto& m_scene : m_scenes)
	{
		delete m_scene;
		m_scene = nullptr;
	}*/

	m_scenes.clear();

	m_index_scene.clear();
}

////////////////////////////// COMPONENTS MANAGEMENT //////////////////////////////////////////
// TODO: Create special "Boolean type structure" to put as return type => Get an error message (pretty easily) in ImGui :D
// Usage example (in ImGui): m_scene_manager->add_component(TEST, 0).message
bool has_component(unsigned int entity_mask, unsigned int component_mask)
{
	return (entity_mask & component_mask) == component_mask;
}

BooleanCustom SceneManager::add_component(unsigned int component_type, unsigned int entity_id)
{
	// check if entity_id is valid (in entity list range)
	/*if (entity_id >= this->active_scene()->getEntities().size())
	{
		return BooleanCustom(false, "[out of range] Entity ID does not exists");
	}*/

	// Add component type to entity's mask
	auto &entity_mask = this->active_scene()->getEntities().get(entity_id)->mask;

	if (component_type == COMPONENT_SPRITE)
	{
		if (has_component(entity_mask, COMPONENT_SPRITE))
		{
			// Sprite component already attached to entity
			return BooleanCustom(false, "Error: Could not add Sprite component.\nThis entity already have a Sprite component");
		}
		else
		{
			this->new_sprite(entity_id);
			this->active_scene()->getEntities().get(entity_id)->mask |= component_type; // TODO: Simplify call or make a reference call
			return BooleanCustom(true, "Successfully added Sprite component");
		}
	}

	// TODO: Put Box2D parameters via the mask
	if (component_type == COMPONENT_BOX2DPHYSICS) // Can only have physics if the entity has a Sprite
	{
		if (!has_component(entity_mask, COMPONENT_SPRITE))
			return BooleanCustom(false, "Error: Could not add BoxPhysics component\nPlease add a Sprite component first !");

		if (has_component(entity_mask, COMPONENT_BOX2DPHYSICS))
		{
			// BoxPhysics component already attached to entity
			return BooleanCustom(false, "Error: Could not add BoxPhysics component.\nThis entity already have a BoxPhysics component");
		}
		else
		{
			// TODO: Thomas, you can solve the BoxPhysics no-param constructor here ;D
			this->addBox2D(this->active_scene()->getEntities().get(entity_id), this->m_active_scene->getSprites().get(entity_id), true);
			this->active_scene()->getEntities().get(entity_id)->mask |= component_type;
			return BooleanCustom(true, "Successfully added BoxPhysics component");
		}
	}
	if (component_type == COMPONENT_INPUT)
	{
		if (!has_component(entity_mask, COMPONENT_SPRITE))
			return BooleanCustom(false, "Error: Could not add BoxPhysics component\nPlease add a Sprite component first !");

		if (has_component(entity_mask, COMPONENT_INPUT))
		{
			// Input component already attached to entity
			return BooleanCustom(false, "Error: Could not add Input component.\nThis entity already have an Input component");
		}
		else
		{
			this->addInput(this->active_scene()->getEntities().get(entity_id));
			this->active_scene()->getEntities().get(entity_id)->mask |= component_type;
			return BooleanCustom(true, "Successfully added Input component");
		}
	}

	return BooleanCustom(false, "Could not add component: Unknown Type");
}

// NOTE: In fact, it gets all Components TYPES
std::vector<unsigned int> SceneManager::get_components(unsigned int entity_id)
{
	std::vector<unsigned int> entity_component_masks;

	unsigned int entityMask = this->active_scene()->getEntities().get(entity_id)->mask;
	unsigned int component_type = 1;

	for (int i = 0; component_type << i < COMPONENT_TOTAL; ++i)
	{
		unsigned int component_mask = component_type << i;
		if (has_component(entityMask, component_mask))
		{
			entity_component_masks.emplace_back(component_mask);
		}
	}

	return entity_component_masks;
}

void SceneManager::add_entity(std::string name, float x, float y)
{
	m_active_scene->getEntities().add(new Entity(name, ID), ID);
	add_component(COMPONENT_SPRITE, ID);
	get_component<Sprite>(COMPONENT_SPRITE, ID)->Position = glm::vec2(x, y);
	ID++;
}

void SceneManager::remove_entity(unsigned int id)
{
	remove_components(id);
	m_active_scene->getEntities().remove(id);
}

bool SceneManager::remove_components(unsigned int id)
{
	for (int component : this->get_components(id)) {
		remove_component(id, component);
	}
	return false;
}

bool SceneManager::remove_component(unsigned int id, unsigned int component)
{
	if (component == COMPONENT_SPRITE) {
		m_active_scene->getSprites().remove(id);
	}
	else if (component == COMPONENT_INPUT) {
		this->m_active_scene->getInputs().remove(id);
	}
	else if (component == COMPONENT_BOX2DPHYSICS) {
		this->m_active_scene->getBoxPhysics().remove(id);
	}
	else {
		return false;
	}
	this->m_active_scene->getEntities().get(id)->mask -= component;
	return true;
}

// NOTE: Even if it's a generic (return) type, we STILL need to provide the "ComponentType" parameter..
// TODO: Find a way, if possible, to call the method without the need of the "ComponentType" parameter
// TODO: Correct bugs when/if there is no component to find !
// [IMPORTANT] TODO: Replace return type "T*" by "std::shared_ptr<T>" 
// NOTE: This is far from being optimized with all these conditions..
template <typename T>
T* SceneManager::get_component(ComponentType component_type, unsigned entity_id)
{
	const unsigned int entity_mask = this->active_scene()->getEntities().get(entity_id)->mask;



	if (component_type == COMPONENT_SPRITE)
	{
		if (has_component(entity_mask, COMPONENT_SPRITE)) return (T*)this->active_scene()->getSprites().get(entity_id);
	}
	if (component_type == COMPONENT_BOX2DPHYSICS)
	{
		if (has_component(entity_mask, COMPONENT_BOX2DPHYSICS)) return (T*)this->active_scene()->getBoxPhysics().get(entity_id);
	}
	if (component_type == COMPONENT_INPUT)
	{
		if (has_component(entity_mask, COMPONENT_INPUT)) return (T*)(this->active_scene()->getInputs().get(entity_id));
	}

	return (T*)nullptr;
}
