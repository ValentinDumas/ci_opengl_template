#ifndef DREAMINENGINE_SPRITE_H
#define DREAMINENGINE_SPRITE_H

#include "ResourceManager.h"

#include "Texture.h"

#include <glm/vec2.hpp>
#include <glm/vec2.hpp>

class Sprite
{
public:
	// TODO: uglyyyyy !
	Sprite(Texture texture, glm::vec2 position, glm::vec2 size = glm::vec2(32.0f, 32.0f), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f))
		: m_texture(texture), Position(position), Size(size), Rotation(rotation), Color(color) {}

	Texture m_texture;

	glm::vec2 Position, Size; // Scale ?

	float Rotation;

	glm::vec3 Color;
};

#endif // DREAMINENGINE_SPRITE_H
