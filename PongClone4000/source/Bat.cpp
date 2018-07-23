#include "Bat.h"

Bat::Bat(const int id, 
		const int scrWidth, 
		const int scrHeight) : color({ 0,0,0 }),
								batID(id)
{
	switch (batID) {
		case 1: box.x = batMargin;
			break;
		case 2: box.x = scrWidth - batMargin - batWidth;
			break;
	}

	box.y = (scrHeight - batHeight) / 2;
	box.w = batWidth;
	box.h = batHeight;

	position.x = box.x;
	position.y = box.y;
}

Bat::~Bat()
{

}

void Bat::move(const int scrHeight, const double deltaTime)
{
	position.y += direction.y * speed * deltaTime;

	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y + batHeight > scrHeight)
	{
		position.y = scrHeight - batHeight;
	}
}

void Bat::setDirection(const Vector2D newDir)
{
	direction = newDir;
}

void Bat::setDirectionX(const int _x)
{
	direction.x = _x;
}

void Bat::setDirectionY(const int _y)
{
	direction.y = _y;
}

const SDL_Rect& Bat::getBox()
{
	box.x = static_cast<int>(position.x);
	box.y = static_cast<int>(position.y);

	return box;
}