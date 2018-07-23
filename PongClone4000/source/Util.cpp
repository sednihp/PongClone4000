#include "Util.h"

// =======
// POINT2D
// =======
Point2D::Point2D() : x(0), y(0)
{

}

Point2D::Point2D(double _x, double _y) : x(_x), y(_y)
{

}

void Point2D::set(double newX, double newY)
{
	x = newX;
	y = newY;
}


// ========
// VECTOR2D
// ========
Vector2D::Vector2D() : x(0), y(0)
{

}

Vector2D::Vector2D(double _x, double _y) : x(_x), y(_y)
{

}

void Vector2D::set(double newX, double newY)
{
	x = newX;
	y = newY;
}

void Vector2D::normalize()
{
	const double length = sqrt((x*x) + (y*y));

	if (length > 0)
	{
		x /= length;
		y /= length;
	}
}