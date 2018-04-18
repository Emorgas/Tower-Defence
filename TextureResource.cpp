#include "TextureResource.h"



TextureResource::TextureResource(SDL_Texture* texture, const char* resourceName)
{
	_texture = texture;
	_resourceName = resourceName;
	SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
}


TextureResource::~TextureResource()
{
	SDL_DestroyTexture(_texture);
}

std::string TextureResource::GetResourceName()
{
	return _resourceName;
}

SDL_Texture * TextureResource::GetTexture()
{
	return _texture;
}

int TextureResource::GetWidth()
{
	return _width;
}

int TextureResource::GetHeight()
{
	return _height;
}
