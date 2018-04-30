#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureResource.h"

class ResourceManager
{
public:
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();

	void LoadTexturesFromFile(const std::string &file, SDL_Renderer *renderer);
	TextureResource* GetTextureResource(const std::string &resourceName);
private:
	std::map<std::string, TextureResource*> _textures;
	const std::string _defaultImagePath = "res\\images\\defaultImage.png";
	const std::string _defaultImageName = "defaultImage";
	
	void AddTextureResource(const std::string &file, const std::string &resourceName, SDL_Renderer *renderer);
};

