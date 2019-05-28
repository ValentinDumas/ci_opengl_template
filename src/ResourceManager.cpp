/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

#include <glad/glad.h>

#include "stb/stb_image.h"

#include "utils/FileSystem.hpp"

// Instantiate static variables
std::map<std::string, Texture>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

std::list<std::string> supported_texture_extensions = { ".jpg", ".png", ".bmp" };

std::map<std::string, Texture> ResourceManager::GetTexturesBank()
{
	return Textures;
}

unsigned int ResourceManager::CountTextures()
{
	return Textures.size();
}

// TODO: repair valid extension check when loading textures
int ResourceManager::LoadTextures(const std::string& path)
{
	std::string texture_filename;
	std::string texture_extension;
	unsigned int texture_count = 0;

	std::vector<std::string> texture_paths;
    utils::filesystem::get_tree(path, texture_paths, false);

	for (auto & filepath : texture_paths)
	{
		bool is_extension_valid = false;

//		if (!filepath.has_extension()) continue;
//
//		texture_filename = filepath.filename().string();
//		texture_extension = filepath.extension().string();
//
//		// TODO: make a supported extensions list
//		for (auto &supported_extension : supported_texture_extensions)
//		{
//			if (texture_extension == supported_extension) // extension found
//			{
//				is_extension_valid = true; // valid extension
//			}
//		}
//
//		if (!is_extension_valid) continue;

        std::string filename = utils::filesystem::get_filename_without_extension(filepath);
        if(!filename.empty())
        {
            ResourceManager::LoadTexture(filepath.c_str(), GL_TRUE, filename);
            texture_count++;
        } else{
            std::cout << "[info] (LoadTextures) Path " << filepath << " does not match a file path (folder instead ?)" << std::endl;
        }

	}

	return texture_count++;
}

int ResourceManager::LoadShaders(const std::string& path)
{
	// Load Shaders (program, vertex, fragment)
	std::string vertex_filepath;
	std::string fragment_filepath;
	unsigned int file_counter = 0;
	unsigned int shaders_count = 0;

	std::vector<std::string> shader_paths;
	utils::filesystem::get_tree(path, shader_paths, false);

	for(const std::string& shader_path : shader_paths)
	{
//		if(utils::filesystem::is_file(shader_path) && utils::filesystem::has_extension(shader_path)) // We suppose it is a file, with an extension
//		{
		    if(utils::filesystem::get_file_extension(shader_path) == ".vert")
            {
                //TODO: shader file extensions as constants at the top of the resourcemanager file.
                std::string shader_filepath_without_extension = utils::filesystem::get_filepath_without_extension(shader_path);
                vertex_filepath = (shader_filepath_without_extension + ".vert");
                fragment_filepath = (shader_filepath_without_extension + ".frag");

                // Check if fragment shader exists
                if(utils::filesystem::exists(fragment_filepath))
				{
					ResourceManager::LoadShader(vertex_filepath.c_str(), fragment_filepath.c_str(), nullptr, utils::filesystem::get_filename_without_extension(shader_path));
				}
            }
			std::cout << utils::filesystem::get_filepath_without_extension(shader_path) << std::endl;
//		}
	}

//		file_counter++;
//
//		if (vertex_filename.empty() || fragment_filename.empty() || file_counter != 2) {}
//		else
//		{
//			ResourceManager::LoadShader((path + "\\" + vertex_filename).c_str(), (path + "\\" + fragment_filename).c_str(), nullptr, remove_extension(filepath.filename().string()));
//			shaders_count++;
//		}
//
//		if (file_counter == 2)
//		{
//			vertex_filename = "";
//			fragment_filename = "";
//			file_counter = 0;
//		}
//
//		/*std::cout << i.string() << std::endl;
//		std::cout << i.filename() << std::endl;
//		std::cout << remove_extension(i.filename().string()) << std::endl;
//		std::cout << i.extension() << std::endl;
//		std::cout << "------------" << std::endl;*/
//	}

	return shaders_count;
}

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
	// Create Texture object
	Texture texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height, num_channels; // TODO: Include this in Texture structure
	unsigned char* image = stbi_load(file, &width, &height, &num_channels, texture.Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);

	if(image == nullptr)
	{
		std::cout << "[warning] Image " << std::string(file) << " cannot be loaded." << std::endl;
	}

	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	stbi_image_free(image);
	return texture;
}