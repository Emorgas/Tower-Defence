#pragma once
#include "TextureResource.h"
#include <SDL.h>

class Sprite
{
public:
	Sprite();
	Sprite(TextureResource *texture, float xPos, float yPos, float xScale, float yScale);
	Sprite(TextureResource *texture, float xPos, float yPos);
	Sprite(TextureResource *texture, SDL_Point *position, SDL_Point *scale);
	Sprite(TextureResource *texture, SDL_Point *position);
	Sprite(TextureResource *texture);
	~Sprite();

	void Draw(SDL_Renderer *renderer);
private:
	TextureResource *_texture;
	SDL_Point _position;
	SDL_Point _scale;
};
