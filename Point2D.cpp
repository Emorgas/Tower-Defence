#include "Point2D.h"

namespace Engine
{
	Point2D::Point2D()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	Point2D::Point2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point2D::Point2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
}