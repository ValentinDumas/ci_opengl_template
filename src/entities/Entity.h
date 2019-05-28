//
// Created by ThomasBI on 06/03/2018.
//

#ifndef DREAMINENGINE_ENTITY_H
#define DREAMINENGINE_ENTITY_H

#include <string>

struct Entity {
	std::string name;
	unsigned int id;
	
	unsigned int mask = 0; // Entity bit component mask

	Entity(std::string _name, unsigned int _id) : name(_name), id(_id) {}
};

#endif //DREAMINENGINE_ENTITY_H
