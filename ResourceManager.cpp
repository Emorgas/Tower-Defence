#include "ResourceManager.h"
#include "document.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace rapidjson;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
{
	AddTextureResource(_defaultImagePath, _defaultImageName, renderer, NULL);
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
			AddTextureResource(filePath, fileName, renderer, NULL);
		}
		fileToLoad.close();
	}
}

void ResourceManager::LoadTextureAtlasFromJSON(const string &file, const string &atlasPath, SDL_Renderer *renderer)
{
	ifstream fileToLoad(file.c_str());
	string jsonString;
	Document jsonDoc;
	SDL_Texture *atlasTexture = IMG_LoadTexture(renderer, atlasPath.c_str());
	if (atlasTexture == nullptr)
	{
		cout << "Atlas image load error: " << IMG_GetError() << endl;
	}
	if (fileToLoad.is_open())
	{
		stringstream sStream;
		sStream << fileToLoad.rdbuf();
		jsonString = sStream.str();
		jsonDoc.Parse(jsonString.c_str());
		if (jsonDoc.HasMember("frames"))
		{
			const Value& texFrames = jsonDoc["frames"];
			for (auto& tex : texFrames.GetArray())
			{
				string resourceName = tex["filename"].GetString();
				// Remove file extention from the name
				resourceName = resourceName.substr(0, resourceName.find("."));
				const Value& frame = tex["frame"];
				SDL_Rect *srcRect = new SDL_Rect();
				srcRect->x = frame["x"].GetInt();
				srcRect->y = frame["y"].GetInt();
				srcRect->w = frame["w"].GetInt();
				srcRect->h = frame["h"].GetInt();
				AddTextureResource(atlasTexture, resourceName, srcRect);
			}
		}
	}
}

void ResourceManager::AddTextureResource(const string &file, const string &resourceName, SDL_Renderer *renderer, SDL_Rect *srcRect)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
	if (_textures.count(resourceName) > 0)
	{
		cout << "Error! A texture resource already exists with the name " << resourceName.c_str() << "! Please use another name." << endl;
		return;
	}
	if (texture != nullptr)
	{
		TextureResource* texRes = new TextureResource(texture, resourceName.c_str(), srcRect);
		_textures.emplace(resourceName.c_str(), texRes);
	}
	else
	{
		cout << "Call to IMG_LoadTexture failed with file: " << file.c_str() << endl;
	}
}

void ResourceManager::AddTextureResource(SDL_Texture *tex, const string &resourceName, SDL_Rect *srcRect)
{
	if (_textures.count(resourceName) > 0)
	{
		cout << "Error! A texture resource already exists with the name " << resourceName.c_str() << "! Please use another name." << endl;
		return;
	}
	if (tex != nullptr)
	{
		TextureResource *texRes = new TextureResource(tex, resourceName.c_str(), srcRect);
		_textures.emplace(resourceName.c_str(), texRes);
	}
	else
	{
		cout << "Received null texture for resource " << resourceName.c_str() << endl;
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
