#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureResource.h"

namespace Engine
{
	class ResourceManager
	{
	public:
		static ResourceManager& GetInstance();

		ResourceManager(ResourceManager const&) = delete;
		void operator=(ResourceManager const&) = delete;

		void Init(SDL_Renderer * renderer);
		void CleanupResources();
		void LoadTexturesFromFile(const std::string &file, SDL_Renderer *renderer);
		void LoadTextureAtlasFromJSON(const std::string &file, const std::string &imagePath, SDL_Renderer *renderer);
		TextureResource* GetTextureResource(const std::string &resourceName);
	private:
		ResourceManager() { }

		std::map<std::string, TextureResource*> _textures;
		const std::string _defaultImagePath = "res\\images\\defaultImage.png";
		const std::string _defaultImageName = "defaultImage";

		void AddTextureResource(const std::string &file, const std::string &resourceName, SDL_Renderer *renderer, SDL_Rect *srcRect);
		void AddTextureResource(SDL_Texture *tex, const std::string &resourceName, SDL_Rect *srcRect);
	};
}