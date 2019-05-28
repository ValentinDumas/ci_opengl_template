//
// Created by ThomasBI on 30/01/2018.
//

#include <scenes/Scene.h>
#include <scenes/SceneManager.h>

Scene::Scene(SceneManager *sceneManager, const std::string &sceneName) : m_sceneManager(sceneManager),
m_name(sceneName),
m_box_physics_system(), m_input_system(),
m_sprites(), m_box_physique(), m_inputs(), m_entities() {
	m_world = new b2World(b2Vec2(0.0, 9.81));
}

void Scene::update(std::vector<InputEnum> inputs) {
	m_box_physics_system.update(m_box_physique, m_sprites);
	m_input_system.update(inputs, m_inputs, m_sprites);
	// TODO: put "timeStep=1.0f/60.0f" to fit the 60FPS refresh rate => realistic simulation
	m_world->Step(1.0 / 60.0, 8, 3);
}

void Scene::render() {
	for (auto &sprite : m_sprites.getVector()) {
		m_sceneManager->update_sprite(sprite);
		m_sceneManager->render_sprite(sprite);
	}
}

Scene::~Scene() {
	for (int i = 0; i < m_box_physique.getVector().size(); i++) {
		m_world->DestroyBody(m_box_physique.getVector()[i]->getBody());
	}
	m_sprites.kill();
	m_box_physique.kill();
	delete m_world;
	delete m_sceneManager;
}

void Scene::add_sprite(unsigned int entity_id, Sprite *sprite) {
	m_sprites.add(sprite, entity_id);
}

void Scene::add_box_physics(Entity *entity, int x, int y, int w, int h, bool dyn) {
	m_box_physique.add(new BoxPhysics(), entity->id);
	m_box_physique.get(entity->id)->addRec(m_world, x, y, w, h, dyn);
	m_world->SetContactListener(m_box_physique.get(entity->id));
}

void Scene::add_input(Entity *entity) {
	m_inputs.add(new Input(), entity->id);
}

