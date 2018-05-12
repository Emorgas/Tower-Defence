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

	Sprite::Sprite(TextureResource *texture, Point2D *position, Point2D *scale)
	{
		Sprite(texture, position->x, position->y, scale->x, scale->y);
	}
	Sprite::Sprite(TextureResource *texture, Point2D *position)
	{
		Sprite(texture, position->x, position->y, 1.0f, 1.0f);
	}
	Sprite::Sprite(TextureResource *texture)
	{
		Sprite(texture, 0.0f, 0.0f, 1.0f, 1.0f);
	}

	Sprite::~Sprite()
	{
		// Null the texture reference, textures a cleaned up in resource manager
		_texture = nullptr;
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

	Point2D Sprite::GetPosition()
	{
		return _position;
	}

	Point2D Sprite::GetScale()
	{
		return _scale;
	}

	void Sprite::SetPosition(Point2D newPos)
	{
		_position.x = newPos.x;
		_position.y = newPos.y;
	}

	void Sprite::SetPosition(int x, int y)
	{
		_position.x = x;
		_position.y = y;
	}

	void Sprite::SetScale(Point2D newScale)
	{
		_scale.x = newScale.x;
		_scale.y = newScale.y;
	}

	void Sprite::SetXScale(int xScale)
	{
		_scale.x = xScale;
	}

	void Sprite::SetYScale(int yScale)
	{
		_scale.y = yScale;
	}
}