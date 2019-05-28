#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
	unsigned int ID;

	Shader() { }

	Shader  &Use();

	// Compiles the shader from given source code
	void    Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);

	Shader& SetFloat(const char *name, float value, bool useShader = false);
	Shader&    SetInteger(const char *name, int value, bool useShader = false);
	Shader&    SetVector2f(const char *name, float x, float y, bool useShader = false);
	Shader&    SetVector2f(const char *name, const glm::vec2 &value, bool useShader = false);
	Shader&    SetVector3f(const char *name, float x, float y, float z, bool useShader = false);
	Shader&    SetVector3f(const char *name, const glm::vec3 &value, bool useShader = false);
	Shader&    SetVector4f(const char *name, float x, float y, float z, float w, bool useShader = false);
	Shader&    SetVector4f(const char *name, const glm::vec4 &value, bool useShader = false);
	Shader&    SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader = false);
private:
	void    checkCompileErrors(unsigned int object, std::string type);
};

#endif
