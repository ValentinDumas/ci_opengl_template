#ifndef DREAMINENGINE_EVENTSUBSCRIBER_H
#define DREAMINENGINE_EVENTSUBSCRIBER_H

class Scene;

class BaseEventSubscriber
{
public:
	virtual ~BaseEventSubscriber() {};
};

/**
* Subclass this as EventSubscriber<EventType> and then call Scene::subscribe() in order to subscribe to events. Make sure
* to call Scene::unsubscribe() or Scene::unsubscribeAll() when your subscriber is deleted!
*/
template<typename T>
class EventSubscriber : public BaseEventSubscriber
{
public:
	virtual ~EventSubscriber() {}

	/**
	* Called when an event is emitted by the scene.
	*/
	virtual void receive(Scene* scene, const T& event) = 0;
};

#endif // DREAMINENGINE_EVENTSUBSCRIBER_H