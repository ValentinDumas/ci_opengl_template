/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "components/Shader.h"
#include "components/Texture.h"

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class ResourceManager
{
public:
	// Resource storage
	static std::map<std::string, Shader>    Shaders;
	static std::map<std::string, Texture> Textures;
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader   LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);
	// Retrieves a stored sader
	static Shader   GetShader(std::string name);
	// Loads (and generates) a texture from file
	static Texture LoadTexture(const char *file, bool alpha, std::string name);
	// Retrieves a stored texture
	static Texture GetTexture(std::string name);
	// Properly de-allocates all loaded resources
	static void      Clear();
	// Get all the Bank which contains all loaded Textures
	static std::map<std::string, Texture> GetTexturesBank();
	// Count the number of loaded textures
	static unsigned int CountTextures();
	// Load a whole bunch of shaders from a specific path
	static int LoadShaders(const std::string& path);
	// Load a whole bunch of textures from a specific path
	static int LoadTextures(const std::string& path);
private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader    loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif