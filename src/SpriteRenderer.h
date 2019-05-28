#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "components/Shader.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Texture;

class SpriteRenderer
{
public:
	SpriteRenderer(Shader shader);

	~SpriteRenderer();

	void DrawSprite(Texture &texture,
		glm::vec2 position,
		glm::vec2 size = glm::vec2(10, 10),
		float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f),
		bool mirror = false);

	// TODO: do something with this method or delete it
	void ChangeVerticeData(float *vertices);

private:
	Shader shader;
	unsigned int quadVAO, quadVBO;

	void initRenderData();
};

#endif // SPRITE_RENDERER_H