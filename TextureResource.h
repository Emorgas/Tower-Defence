#pragma once
#include <string>
#include <SDL.h>

class TextureResource
{
public:
	TextureResource(SDL_Texture* texture, const char* resourceName);
	~TextureResource();
	std::string GetResourceName();
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
private:
	std::string _resourceName;
	SDL_Texture* _texture;
	int _width;
	int _height;
};

