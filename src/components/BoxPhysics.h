//
// Created by ThomasBI on 05/03/2018.
//

#ifndef DREAMINENGINE_BOXPHYSICS_H
#define DREAMINENGINE_BOXPHYSICS_H

#include <Box2D/Box2D.h>

class BoxPhysics : public b2ContactListener {
private:
	b2Body * body;
	b2BodyDef bodydef;
public:
	BoxPhysics() : bodydef() { body = nullptr; }
	b2Body* addRec(b2World* world, int x, int y, int w, int h, bool dyn = true);
	b2Body* getBody() { return body; }
	b2BodyDef& getBodyDef() { return bodydef;  }

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact* contact);
};


#endif //DREAMINENGINE_BOXPHYSICS_H
