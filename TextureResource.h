#pragma once
#include <string>
#include <SDL.h>

class TextureResource
{
public:
	TextureResource(SDL_Texture* texture, const char* resourceName, SDL_Rect* srcRect);
	~TextureResource();
	std::string GetResourceName();
	SDL_Texture* GetTexture();
	int GetWidth();
	int GetHeight();
	SDL_Rect * GetSourceRect();
private:
	std::string _resourceName;
	SDL_Texture* _texture;
	SDL_Rect* _srcRect = NULL;
	int _width;
	int _height;
};

