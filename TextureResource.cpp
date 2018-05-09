#include "TextureResource.h"

namespace Engine
{
	TextureResource::TextureResource(SDL_Texture* texture, const char* resourceName, SDL_Rect* srcRect)
	{
		_texture = texture;
		_resourceName = resourceName;
		_srcRect = srcRect;
		if (srcRect == NULL)
		{
			SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
		}
		else
		{
			_width = _srcRect->w;
			_height = _srcRect->h;
		}
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

	SDL_Rect* TextureResource::GetSourceRect()
	{
		return _srcRect;
	}
}