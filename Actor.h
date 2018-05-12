#pragma once
#include "Sprite.h"

namespace Engine
{
	class Actor : public Sprite
	{
	public:
		Actor(TextureResource* texture, float xPos, float yPos, float xScale, float yScale);
		void Update(float dt);
		~Actor();
	};
}