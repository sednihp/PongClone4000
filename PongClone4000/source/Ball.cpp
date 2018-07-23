#include "Ball.h"

Ball::Ball(const std::string& img, const int _x, const int scrHeight) : Sprite(img), moving(false), speed(0)
{
	position.x = _x + radius;
	position.y = ((scrHeight - ballWidth) / 2) + radius;
}

Ball::~Ball()
{

}

const Point2D Ball::getPosition()
{
	return { position.x - radius, position.y - radius };
}

void Ball::move(const int scrHeight, const int scrWidth, const SDL_Rect& leftBat, const SDL_Rect& rightBat, const double dTime)
{
	direction.normalize();

	position.x += direction.x * speed * dTime;

	if (hasCollided(leftBat))
	{
		position.x = leftBat.x + leftBat.w + radius;
		direction.x *= -1;
		//direction.y += p1YVel * 0.005;
		speed *= 1.05;
	}
	else if (hasCollided(rightBat))
	{
		position.x = rightBat.x - radius;
		direction.x *= -1;
		//direction.y += p2YVel * 0.005;
		speed *= 1.05;
	}

	if (position.x + radius < 0)
	{
		direction.x *= -1;
	}
	else if (position.x - radius > scrWidth)
	{
		direction.x *= -1;
	}

	const double moveY = direction.y * speed * dTime;
	position.y += moveY;

	if (position.y - radius < 0)
	{
		direction.y *= -1;
	}
	else if (position.y + radius > scrHeight)
	{
		direction.y *= -1;
	}
	else if (hasCollided(leftBat) || hasCollided(rightBat))
	{
		position.y -= moveY;
		direction.y *= -1;
		speed *= 1.05;
	}
}

bool Ball::hasCollided(const SDL_Rect& rect) 
{
	double closestX, closestY;

	if (position.x < rect.x)
		closestX = rect.x;
	else if (position.x > rect.x + rect.w)
		closestX = rect.x + rect.w;
	else
		closestX = position.x;

	if (position.y < rect.y)
		closestY = rect.y;
	else if (position.y > rect.y + rect.h)
		closestY = rect.y + rect.h;
	else
		closestY = position.y;

	if (distance(position.x, position.y, closestX, closestY) < radius)
		return true;

	return false;
}

const double Ball::distance(const double x1, const double y1, const double x2, const double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Ball::startMoving(const double xDir, const double yDir)
{
	moving = true;

	const double randomX = rand() % 20 + 50;
	const double randomY = rand() % 20 + 50;

	direction.x = xDir * randomX;
	direction.y = yDir * randomY;

	speed = 300;
}