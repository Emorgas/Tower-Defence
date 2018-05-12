#pragma once
#include "TextureResource.h"
#include "Point2D.h"
#include <SDL.h>

namespace Engine
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(TextureResource *texture, float xPos, float yPos, float xScale, float yScale);
		Sprite(TextureResource *texture, float xPos, float yPos);
		Sprite(TextureResource *texture, Point2D *position, Point2D *scale);
		Sprite(TextureResource *texture, Point2D *position);
		Sprite(TextureResource *texture);
		~Sprite();

		void Draw(SDL_Renderer *renderer);
		float GetWidth();
		float GetHeight();
		Point2D GetPosition();
		Point2D GetScale();
		void SetPosition(Point2D newPos);
		void SetPosition(int x, int y);
		void SetScale(Point2D newScale);
		void SetXScale(int xScale);
		void SetYScale(int yScale);
	protected:
		TextureResource* _texture;
		Point2D _position;
		Point2D _scale;
		float _width;
		float _height;
	};
}