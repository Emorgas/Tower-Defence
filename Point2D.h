#pragma once
namespace Engine
{
	class Point2D
	{
	public:
		Point2D();
		Point2D(int x, int y);
		Point2D(float x, float y);
		float x, y;
	};
}