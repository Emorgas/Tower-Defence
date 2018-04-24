#include "Sprite.h"



Sprite::Sprite()
{
	// TODO: Create resource manager singleton for default allocation
	//_texture = 
}

Sprite::Sprite(TextureResource *texture, float xPos, float yPos, float xScale, float yScale)
{
	_texture = texture;
	_position.x = xPos;
	_position.y = yPos;
	_scale.x = xScale;
	_scale.y = yScale;
}

Sprite::Sprite(TextureResource *texture, float xPos, float yPos)
{
	Sprite(_texture, xPos, yPos, 1.0f, 1.0f);
}

Sprite::Sprite(TextureResource *texture, SDL_Point *position, SDL_Point *scale)
{
	Sprite(texture, position->x, position->y, scale->x, scale->y);
}
Sprite::Sprite(TextureResource *texture, SDL_Point *position)
{
	Sprite(texture, position->x, position->y, 1.0f, 1.0f);
}
Sprite::Sprite(TextureResource *texture)
{
	Sprite(texture, 0.0f, 0.0f, 1.0f, 1.0f);
}

Sprite::~Sprite()
{
}

void Sprite::Draw(SDL_Renderer *renderer)
{
	SDL_Rect dst;
	dst.x = _position.x;
	dst.y = _position.y;
	dst.w = _texture->GetWidth() * _scale.x;
	dst.h = _texture->GetHeight() * _scale.y;
	SDL_RenderCopy(renderer, _texture->GetTexture(), NULL, &dst);
}
