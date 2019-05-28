//
// Created by ThomasBI on 05/03/2018.
//

#include <Box2D/Dynamics/b2Body.h>
#include "components/BoxPhysics.h"
#include <iostream>

b2Body* BoxPhysics::addRec(b2World *world, int x, int y, int w, int h, bool dyn)
{
	bodydef.position.Set(x, y);
	bodydef.gravityScale = 5;


	if (dyn)
		bodydef.type = b2_dynamicBody;
	body = world->CreateBody(&bodydef);

	b2PolygonShape bshape;
	bshape.SetAsBox(w, h);

	b2FixtureDef fixturedef;
	fixturedef.shape = &bshape;
	fixturedef.density = 5.0;
	fixturedef.restitution = 1.0;
	
	body->CreateFixture(&fixturedef);

	// TODO: nullptr to remove ! should return a value (did this to Compile)
	return nullptr;
}

void BoxPhysics::BeginContact(b2Contact * contact)
{
	//std::cout << "begin contact" << std::endl;
	body->ApplyForce(b2Vec2(90, 0), body->GetWorldCenter(), true);
}

void BoxPhysics::EndContact(b2Contact * contact)
{
	//std::cout << "end contact" << std::endl;
}
