#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	AddTextureResource(_defaultImagePath, _defaultImageName, renderer);
}


ResourceManager::~ResourceManager()
{
	for (std::map<std::string, TextureResource*>::iterator it = _textures.begin(); it != _textures.end(); ++it)
		delete it->second;
}

void ResourceManager::AddTextureResource(const std::string &file, const std::string &resourceName, SDL_Renderer *renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	if (_textures.count(resourceName) > 0)
	{
		std::cout << "Error! A texture resource already exists with the name " << resourceName.c_str() << "! Please use another name." << std::endl;
		return;
	}
	if (texture != nullptr)
	{
		TextureResource* texRes = new TextureResource(texture, resourceName.c_str());
		_textures.emplace(resourceName.c_str(), texRes);
	}
	else
	{
		std::cout << "Call to IMG_LoadTexture failed with file: " << file.c_str() << std::endl;
	}
}

TextureResource* ResourceManager::GetTextureResource(const std::string &resourceName)
{
	if (_textures.count(resourceName) == 0)
	{
		return _textures.find(_defaultImageName)->second;
	}
	return _textures.find(resourceName)->second;
}
