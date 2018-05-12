#include "Actor.h"
#include "EngineRunner.h"

namespace Engine
{
	Actor::Actor(TextureResource* texture, float xPos, float yPos, float xScale, float yScale)
		: Sprite(texture, xPos, yPos, xScale, yScale)
	{
		EngineRunner::GetInstance().AddActorToUpdate(this);
	}

	void Actor::Update(float dt)
	{
		_position.x += 50.0f * dt;
	}

	Actor::~Actor()
	{
	}
}