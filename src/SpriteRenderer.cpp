#include "components/Texture.h"
#include "SpriteRenderer.h"

#include <glad/glad.h>

SpriteRenderer::SpriteRenderer(Shader shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position,
	glm::vec2 size, float rotate, glm::vec3 color, bool mirror)
{
	// Prepare transformations
	this->shader.Use();
	glm::mat4 model(1.0f);

	// Move object to position
	model = glm::translate(model, glm::vec3(position, 0.0f));

	// Rotation method
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	// Scale the object from 1.0/unity
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.SetMatrix4("model", model); // for shader .vert
	this->shader.SetVector3f("spriteColor", color); // for shader .frag
	this->shader.SetInteger("mirror", mirror);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D,0);
}

void SpriteRenderer::ChangeVerticeData(GLfloat *vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Position // Texture

		// first triangle
		1.0f, 1.0f, 1.0f, 1.0f, // top right
		-1.0f, -1.0f, 0.0f, 0.0f, // bottom left
		-1.0f, 1.0f, 0.0f, 1.0f, // top left
		
		// second triangle
		1.0f, 1.0f, 1.0f, 1.0f, // top right
		1.0f, -1.0f, 1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &this->quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
