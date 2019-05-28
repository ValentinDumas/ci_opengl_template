//
// Created by ThomasBI on 30/01/2018.
//

#ifndef DREAMINENGINE_SCENE_H
#define DREAMINENGINE_SCENE_H

#include <string>
#include <unordered_map>

#include <components/BoxPhysics.h>
#include <entities/Entity.h>
#include <utils/ComponentStore.h>
#include <systems/BoxPhysicsSystem.h>
#include <systems/InputSystem.h>
#include <components/Sprite.h>
#include <components/Input.h>
#include <utils/InputEnum.h>

#include <utils/typ.h>
#include <events/Events.h>
#include <events/EventSubscriber.h>

class SceneManager;

class Scene {
public:
	Scene(SceneManager *sceneManager, const std::string &sceneName);

	void update(std::vector<InputEnum> inputs);

	void render();

	void add_sprite(unsigned int entity_id, Sprite* sprite);

	void add_box_physics(Entity *entity, int x, int y, int w, int h, bool dyn);

	void add_input(Entity *entity);

	void setName(std::string name) { m_name = name; }

	std::string getName() const { return m_name; }

	b2World* getWorld() const { return m_world; }

	ComponentStore<Entity>& getEntities() { return m_entities; }

	ComponentStore<Sprite>& getSprites() { return m_sprites; }

	ComponentStore<BoxPhysics>& getBoxPhysics() { return m_box_physique; }

	ComponentStore<Input>& getInputs() { return m_inputs; }

	~Scene();

	/**
	* Subscribe to an event.
	*/
	template<typename T>
	void subscribe(EventSubscriber<T>* subscriber)
	{
		auto index = getTypeIndex<T>();
		auto found = subscribers.find(index);
		if (found == subscribers.end())
		{
			std::vector<BaseEventSubscriber*> subList;
			subList.push_back(subscriber);

			subscribers.insert({ index, subList });
		}
		else
		{
			found->second.push_back(subscriber);
		}
	}

	/**
	* Unsubscribe from an event.
	*/
	template<typename T>
	void unsubscribe(EventSubscriber<T>* subscriber)
	{
		auto index = getTypeIndex<T>();
		auto found = subscribers.find(index);
		if (found != subscribers.end())
		{
			found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());
			if (found->second.size() == 0)
			{
				subscribers.erase(found);
			}
		}
	}

	/**
	* Unsubscribe from all events. Don't be afraid of the void pointer, just pass in your subscriber as normal.
	*/
	void unsubscribeAll(void* subscriber)
	{
		for (auto kv : subscribers)
		{
			/*kv.second.erase(std::remove(kv.second.begin(), kv.second.end(), subscriber), kv.second.end());
			if (kv.second.size() == 0)
			{
			subscribers.erase(kv.first);
			}*/
		}
	}

	/**
	* Emit an event. This will do nothing if there are no subscribers for the event type.
	*/
	template<typename T>
	void emit(const T& event)
	{
		auto found = subscribers.find(getTypeIndex<T>());
		if (found != subscribers.end())
		{
			for (auto* base : found->second)
			{
				auto* sub = reinterpret_cast<EventSubscriber<T>*>(base);
				sub->receive(this, event);
			}
		}
	}
private:
	// Scene data
	std::string m_name;
	SceneManager* m_sceneManager = nullptr;

	// Box2D
	b2World* m_world;
	BoxPhysicsSystem m_box_physics_system;
	InputSystem m_input_system;

	// Scene entities
	ComponentStore<Entity> m_entities;
	// Scene components
	ComponentStore<BoxPhysics> m_box_physique;
	ComponentStore<Sprite> m_sprites;
	ComponentStore<Input> m_inputs;

	// Subscribers' list
	std::unordered_map<TypeIndex, std::vector<BaseEventSubscriber*>, std::hash<TypeIndex>> subscribers;
};

#endif //DREAMINENGINE_SCENE_H
