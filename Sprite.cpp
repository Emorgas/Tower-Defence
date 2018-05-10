#include "Sprite.h"
#include "ResourceManager.h"
namespace Engine
{
	Sprite::Sprite()
	{
		_texture = ResourceManager::GetInstance().GetTextureResource("defaultImage");
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
		SDL_RenderCopy(renderer, _texture->GetTexture(), _texture->GetSourceRect(), &dst);
	}

	float Sprite::GetWidth()
	{
		return _texture->GetWidth() * _scale.x;
	}

	float Sprite::GetHeight()
	{
		return _texture->GetHeight() * _scale.y;
	}

	SDL_Point Sprite::GetPosition()
	{
		return _position;
	}

	SDL_Point Sprite::GetScale()
	{
		return _scale;
	}

	void Sprite::MovePos(SDL_Point moveVector)
	{
		_position.x = _position.x + moveVector.x;
		_position.y = _position.y + moveVector.y;
	}
}