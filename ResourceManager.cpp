#include "ResourceManager.h"
#include <iostream>
#include <fstream>

using namespace std;
ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	AddTextureResource(_defaultImagePath, _defaultImageName, renderer);
}


ResourceManager::~ResourceManager()
{
	for (map<string, TextureResource*>::iterator it = _textures.begin(); it != _textures.end(); ++it)
		delete it->second;
}

void ResourceManager::LoadTexturesFromFile(const string & file, SDL_Renderer *renderer)
{
	string line;
	ifstream fileToLoad(file.c_str());
	if (fileToLoad.is_open())
	{
		size_t pos = 0;
		string filePath;
		string fileName;
		while (std::getline(fileToLoad, line))
		{
			pos = 0;
			pos = line.find(";");
			filePath = line.substr(0, pos);
			fileName = line.substr(pos + 1, line.length());
			AddTextureResource(filePath, fileName, renderer);
		}
		fileToLoad.close();
	}
}

void ResourceManager::AddTextureResource(const string &file, const string &resourceName, SDL_Renderer *renderer)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	if (_textures.count(resourceName) > 0)
	{
		cout << "Error! A texture resource already exists with the name " << resourceName.c_str() << "! Please use another name." << endl;
		return;
	}
	if (texture != nullptr)
	{
		TextureResource* texRes = new TextureResource(texture, resourceName.c_str());
		_textures.emplace(resourceName.c_str(), texRes);
	}
	else
	{
		cout << "Call to IMG_LoadTexture failed with file: " << file.c_str() << endl;
	}
}

TextureResource* ResourceManager::GetTextureResource(const string &resourceName)
{
	if (_textures.count(resourceName) == 0)
	{
		return _textures.find(_defaultImageName)->second;
	}
	return _textures.find(resourceName)->second;
}
